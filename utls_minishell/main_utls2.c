/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utls2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:46:29 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 01:09:14 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *input)
{
	printf("syntax error\n");
	g_status.exit_status = 258;
	free (input);
}

void	free_end(t_exc *cmd, t_token *token, char *input)
{
	ft_lstclear(&cmd);
	ft_lstclear2(token);
	free (input);
}

void	execut_main(t_exc *cmd, t_env **myenv, t_var var, t_exp **myexp)
{
	t_exc	*tmp;

	tmp = cmd;
	while (cmd && cmd->next)
	{
		ft_exec_mult(cmd, myenv, &var, myexp);
		cmd = cmd->next;
	}
	ft_exec(cmd, myenv, &var, myexp);
	ft_wait_exit(cmd, &var);
	while (tmp)
	{
		if (tmp->fdin != 0)
			close(tmp->fdin);
		if (tmp->fdout != 1)
			close(tmp->fdout);
		tmp = tmp->next;
	}
}
