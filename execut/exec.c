/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:37:21 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 19:41:28 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_mult(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	pid_t	pid;

	ft_catch_signal();
	if (pipe(var->fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_status.exit_status = 1;
		exit (1);
	}
	else if (pid == 0)
	{
		if (cmd->fdin == -1 || cmd->fdout == -1)
			exit(1);
		mult_command(cmd, myenv, var, myexp);
	}
	else
	{
		dup2(var->fd[0], STDIN_FILENO);
		close(var->fd[1]);
		close(var->fd[0]);
	}
}

void	ft_exec(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	ft_catch_signal();
	if (var->size == 1 && is_builtin(cmd))
		singl_built(cmd, myenv, var, myexp);
	else
		singl_comand(cmd, myenv, var, myexp);
	dup2(var->inp, STDIN_FILENO);
	dup2(var->outp, STDOUT_FILENO);
}
