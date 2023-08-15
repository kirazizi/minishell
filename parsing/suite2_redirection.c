/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suite2_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:38:04 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 07:47:56 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_heredocs(t_token *token, t_exc *tcmd, t_env *env)
{
	t_token	*tmp_token;
	t_exc	*tmp_cmd;

	tmp_token = token;
	tmp_cmd = tcmd;
	while ((tmp_token))
	{
		if ((tmp_token)->type == HEREDOC)
			tmp_cmd->fdin = my_here_doc(&tmp_token, env);
		if ((tmp_token) && (tmp_token)->type == PIPE)
			tmp_cmd = tmp_cmd->next;
		tmp_token = (tmp_token)->next;
	}
	return (g_status.heredoc);
}

int	vr_redirection(t_token **token, t_exc *tcmd)
{
	if (((*token)->type == IN && !redirection_input(token, &tcmd)) || \
				((*token)->type == OUT && !redirection_output(token, &tcmd)) || \
			((*token)->type == APPEND && !redirection_append(token, &tcmd)))
		return (0);
	return (1);
}

int	redirection(t_token **token, t_exc **cmd, t_env *env)
{
	t_exc	*tcmd;
	t_token	*old;

	tcmd = *cmd;
	old = (*token);
	if (do_heredocs(*token, tcmd, env))
		return (1);
	while ((*token))
	{
		if (vr_redirection(token, tcmd) == 0)
			return (0);
		*token = (*token)->next;
		while ((*token) && (*token)->type != PIPE && ((*token)->type != IN && 
				(*token)->type != OUT && (*token)->type != APPEND && \
				(*token)->type != HEREDOC))
			*token = (*token)->next;
		if ((*token) && (*token)->type == PIPE)
		{
			tcmd = tcmd->next;
			*token = (*token)->next;
		}
	}
	*token = old;
	return (1);
}
