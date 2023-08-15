/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:43:06 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 01:25:39 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_add(t_token **tokens, char *res)
{
	t_token	*new;
	t_token	*tmp;

	if (!res)
		return ;
	enum test;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	ft_delete_back(&g_status.delete, ft_delete_add(new));
	new->data = res;
	new->type = ft_initialize(res);
	new->next = NULL;
	new->prev = NULL;
	if (!(*tokens))
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	syntax_all(t_token *token, char *tmp)
{
	if (check_syntax(tmp) 
		|| syntax_quote(tmp)
		|| check_syntax_end(tmp) 
		|| check_syntax_list(token))
	{
		return (1);
	}
	return (0);
}

void	version_check(t_token *tmsdp)
{
	if (ft_strcmp(tmsdp->data, "<<") == 0)
		tmsdp->next->is_input = 1;
	else if (tmsdp->is_input != 1)
		tmsdp->is_input = 0;
}

int	ft_check(t_token **token, char *tmp, t_env *env, t_exc **cmd)
{
	t_token	*tmsdp;

	remov_space(tmp);
	thecheck_splite(token, tmp);
	removewhitespacenodes(*token);
	if (syntax_all(*token, tmp))
	{
		syntax_error(tmp);
		return (1);
	}
	tmsdp = *token;
	while (tmsdp)
	{
		version_check(tmsdp);
		ft_check_e(&tmsdp, env);
		tmsdp = tmsdp->next;
	}
	make_prev(*token);
	join_words(token, cmd);
	if (redirection(token, cmd, env) == 0)
		return (0);
	removed_q_suit(cmd);
	return (0);
}
