/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:59:07 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 01:50:11 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*final_path(char **path_spt, char *join)
{
	int		i;

	i = 0;
	while (path_spt[i])
	{
		if (access(ft_strjoin(path_spt[i], join), F_OK) == 0)
			return (ft_strjoin(ft_strdup(path_spt[i]), join));
		i++;
	}
	return (NULL);
}

void	ft_error(char **arg)
{
	if (errno == EACCES)
		ft_printf(2, arg[0], ": Permission denied\n");
	else
		ft_printf(2, arg[0], ": No such file or directory\n");
	exit(126);
}

char	*ft_cmd(t_env *myenv, char **arg)
{
	char	**path_spt;
	char	*join;
	char	*path;

	path = NULL;
	if (check_is_slash(arg[0]))
		ft_error(arg);
	while (myenv)
	{
		if (ft_strcmp(myenv->key, "PATH=") == 0)
			path = myenv->value;
		myenv = myenv->next;
	}
	if (!path)
	{
		ft_printf(2, arg[0], ": No such file or directory\n");
		exit(127);
	}
	path_spt = split_path(path);
	join = ft_strjoin(ft_strdup("/"), arg[0]);
	return (final_path(path_spt, join));
	return (NULL);
}

void	ft_execve(t_env *myenv, t_exc *cmd)
{
	char	**last_myenv;
	char	*cmnd;

	if (check_is_directory(cmd->arg[0]))
		cmnd = cmd->arg[0];
	if (check_is_executabe(cmd->arg[0]))
		cmnd = cmd->arg[0];
	else
		cmnd = ft_cmd(myenv, cmd->arg);
	last_myenv = ft_list_to_char(myenv);
	if (execve(cmnd, cmd->arg, last_myenv) < 0)
	{
		if (errno == ENOENT)
		{
			ft_printf(2, cmd->arg[0], ": No such file or directory\n");
			g_status.exit_status = 127;
		}
		else
		{
			ft_printf(2, cmd->arg[0], ": command not found\n");
			g_status.exit_status = 127;
		}
		exit(127);
	}
}

void	mult_command(t_exc *cmd, t_env **myenv, t_var *var, t_exp **myexp)
{
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
	else
	{
		close(var->fd[0]);
		dup2(var->fd[1], STDOUT_FILENO);
		close(var->fd[1]);
	}
	if (is_builtin(cmd))
	{
		execute_builtin(cmd, myenv, var, myexp);
		g_status.exit_status = 0;
		exit(0);
	}
	else
		ft_execve(*myenv, cmd);
}
