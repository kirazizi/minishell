/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suit_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:50:34 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/14 01:47:10 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rmv_char(char *str, int i)
{
	int		j;

	j = i;
	while (str[++i])
	{
		str[j] = str[i];
		j++;
	}
	str[j] = '\0';
}

void	remove_redrc_qts(char *word)
{
	int		flg;
	char	flg_char;
	int		i;

	flg = 0;
	flg_char = 0;
	i = -1;
	while (word[++i])
	{
		if (!flg && (word[i] == '"' || word[i] == '\''))
		{
			flg_char = word[i];
			flg = i + 1;
		}
		else if (flg && word[i] == flg_char)
		{
			rmv_char(word, i);
			rmv_char(word, flg - 1);
			flg = 0;
			i -= 2;
		}
	}
}

int	red_2_out(t_token **tmp, t_exc **use, char **word, t_token **token)
{
	if ((*tmp)->type != PIPE && (*tmp)->type == OUT && \
		((*tmp) == *token && (((*tmp)->next && (*tmp)->next->type == COMOND) \
				|| (*tmp)->next->type == VAR || (*tmp)->next->type == SQ || \
				(*tmp)->next->type == DQ)))
	{
		*word = ft_strdup((*tmp)->next->data);
		if ((*use)->fdout != 1)
			close((*use)->fdout);
		remove_redrc_qts(*word);
		(*use)->tmpdout = open(*word, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if ((*use)->tmpdout == -1)
		{
			(*use)->fdout = -1;
			if (errno == 13)
				ft_printf(2, *word, " : Permission denied\n");
			else
				ft_printf(2, *word, " : No such file or directory\n");
			return (0);
		}
	}
	return (1);
}

int	red_2_in(t_token **tmp, t_exc **use, char **word, t_token **token)
{
	if ((*tmp)->type != PIPE && (*tmp)->type == IN && ((*tmp) == *token && \
			(((*tmp)->next && (*tmp)->next->type == COMOND) || \
				(*tmp)->next->type == VAR || (*tmp)->next->type == SQ || \
				(*tmp)->next->type == DQ)))
	{
		*word = ft_strdup((*tmp)->next->data);
		if ((*use)->fdin != 0)
			close((*use)->fdin);
		remove_redrc_qts(*word);
		(*use)->tmpdin = open(*word, O_RDWR, 0644);
		if ((*use)->tmpdin == -1)
		{
			(*use)->fdin = -1;
			if (errno == 13)
				ft_printf(2, *word, " : Permission denied\n");
			else
				ft_printf(2, *word, " : No such file or directory\n");
			return (0);
		}
	}
	return (1);
}

int	red_2_appand(t_token **tmp, t_exc **use, char **word, t_token **token)
{
	if ((*tmp)->type != PIPE && (*tmp)->type == APPEND && ((*tmp) == *token && \
			(((*tmp)->next && (*tmp)->next->type == COMOND) || \
				(*tmp)->next->type == VAR)))
	{
		*word = ft_strdup((*tmp)->next->data);
		if ((*use)->fdout != 1)
			close((*use)->fdout);
		remove_redrc_qts(*word);
		(*use)->tmpdout = open(*word, O_CREAT | O_APPEND | O_RDWR, 0644);
		if ((*use)->tmpdout == -1)
		{
			(*use)->fdout = -1;
			if (errno == 13)
				ft_printf(2, *word, " : Permission denied\n");
			else
				ft_printf(2, *word, " : No such file or directory\n");
			return (0);
		}
	}
	return (1);
}
