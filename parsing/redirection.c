/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:13:47 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 20:42:06 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exc_add(t_exc **tokens, char *res)
{
	t_exc	*new;
	t_exc	*tmp;

	if (!res)
		return ;
	new = (t_exc *)malloc(sizeof(t_exc));
	if (!new)
		return ;
	ft_delete_back(&g_status.delete, ft_delete_add(new));
	new->arg = ft_split_use(res, ' ');
	new->fdin = 0;
	new->fdout = 1;
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	join_words(t_token **token, t_exc **cmd)
{
	t_token	*tmp;
	char	*word;

	tmp = *token;
	word = ft_strdup("");
	while (tmp != NULL)
	{
		if (tmp->type != PIPE && (tmp->type == COMOND || tmp->type == SQ || 
				tmp->type == DQ || tmp->type == VAR) && (tmp == *token || 
				(tmp->prev && tmp->prev->type != IN && tmp->prev->type != OUT 
					&& tmp->prev->type != APPEND && 
					tmp->prev->type != HEREDOC)))
		{
			word = ft_strjoin(word, tmp->data);
			word = ft_strjoin(word, " ");
		}
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			ft_exc_add(cmd, word);
			free(word);
			word = ft_strdup("");
		}
		tmp = tmp->next;
	}
	free(word);
}

int	redirection_output(t_token **token, t_exc **cmd)
{
	t_token	*tmp;
	t_exc	*use;
	char	*word;

	use = *cmd;
	use->tmpdout = 1;
	word = NULL;
	tmp = *token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (red_2_out(&tmp, &use, &word, token) == 0)
			return (0);
		tmp = tmp->next;
	}
	if (word && (!tmp || tmp->type == PIPE))
		use->fdout = use->tmpdout;
	free(word);
	return (1);
}

int	redirection_input(t_token **token, t_exc **cmd)
{
	t_token	*tmp;
	t_exc	*use;
	char	*word;

	use = *cmd;
	use->tmpdin = 0;
	word = NULL;
	tmp = *token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (red_2_in(&tmp, &use, &word, token) == 0)
			return (0);
		tmp = tmp->next;
	}
	if (word && (!tmp || tmp->type == PIPE))
	{
		use->fdin = use->tmpdin;
	}
	free(word);
	return (1);
}

int	redirection_append(t_token **token, t_exc **cmd)
{
	t_token	*tmp;
	t_exc	*use;
	char	*word;

	use = *cmd;
	word = NULL;
	tmp = *token;
	use->tmpdout = 1;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (!red_2_appand(&tmp, &use, &word, token))
			return (0);
		tmp = tmp->next;
	}
	if (word && (!tmp || tmp->type == PIPE))
	{
		use->fdout = use->tmpdout;
	}
	free(word);
	return (1);
}
