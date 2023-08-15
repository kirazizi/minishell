/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_singl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:17:55 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 20:49:36 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return ;
	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		ft_cd(cmd, *myenv, *myexp);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(*myenv);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_print_env(*myenv, *var);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		ft_unset(cmd, myenv, myexp);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		cmd_export(cmd, myexp, myenv, *var);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		ft_exit(cmd, var);
	else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
}

int	is_builtin(t_exc *node)
{
	if (!node->arg[0] || !node->arg[0])
		return (0);
	if (ft_strcmp(node->arg[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "unset") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "exit") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "env") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "echo") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "cd") == 0)
		return (1);
	if (ft_strcmp(node->arg[0], "pwd") == 0)
		return (1);
	return (0);
}

void	singl_built(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	if (cmd->fdin != 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	else if (cmd->fdout != 1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	execute_builtin(cmd, myenv, var, myexp);
}

void	execut_singl_cmd(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	if (cmd->fdin == -1 || cmd->fdout == -1)
		exit(1);
	if (cmd->fdin != 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != 1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	if (is_builtin(cmd) && var->size != 1)
	{
		execute_builtin(cmd, myenv, var, myexp);
		g_status.exit_status = 0;
		exit(0);
	}
	else
		ft_execve(*myenv, cmd);
}

void	singl_comand(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_status.exit_status = 1;
		exit (1);
	}
	else if (pid == 0)
		execut_singl_cmd(cmd, myenv, var, myexp);
	else
	{
		close(var->fd[0]);
		close(var->fd[1]);
		close(cmd->fdin);
		close(cmd->fdout);
	}
}
