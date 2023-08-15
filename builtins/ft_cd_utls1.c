/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utls1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:30:49 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 00:20:47 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_part2(t_exc *cmd, t_env *myenv, t_exp *myexp, char *current)
{
	char	*str;

	str = ft_strjoin(get_myenv(myenv, "HOME="), &cmd->arg[1][1]);
	if (chdir(str))
	{
		ft_printf(2, cmd->arg[0], ": HOME not set\n");
		g_status.exit_status = 1;
	}
	else
	{
		if (!current)
			current = ft_get_pwd(myenv);
		update_myenv(myenv, "OLDPWD=", current);
		update_myexp(myexp, "OLDPWD=", current);
		current = getcwd(NULL, 0);
		update_myenv(myenv, "PWD=", current);
		update_myexp(myexp, "PWD=", current);
		g_status.exit_status = 0;
		free(current);
	}
}

void	ft_cd_part3(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current)
{
	char	*joujn9tat;
	char	*str;

	printf("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n");
	joujn9tat = ft_get_pwd(myenv);
	if (!joujn9tat)
		return ;
	str = ft_strjoin(joujn9tat, "/..");
	if (chdir(cmd->arg[1]))
		perror("cd");
	else
	{
		update_myenv(myenv, "OLDPWD=", str);
		update_myexp(myexp, "OLDPWD=", str);
		current = ft_get_pwd(myenv);
		update_myenv(myenv, "PWD=", str);
		update_myexp(myexp, "PWD=", str);
		g_status.exit_status = 0;
		free(current);
	}
}

void	ft_cd_part4(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current)
{
	char	*joujn9tat;
	char	*str;

	printf("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n");
	joujn9tat = ft_get_pwd(myenv);
	if (!joujn9tat)
		return ;
	str = ft_strjoin(joujn9tat, "/.");
	if (chdir(cmd->arg[1]))
		perror("cd");
	else
	{
		update_myenv(myenv, "OLDPWD=", str);
		update_myexp(myexp, "OLDPWD=", str);
		current = ft_get_pwd(myenv);
		update_myenv(myenv, "PWD=", str);
		update_myexp(myexp, "PWD=", str);
		g_status.exit_status = 0;
		free(current);
	}
}

void	ft_cd_part5(t_env *myenv, t_exp *myexp, t_exc *cmd, char *current)
{
	if (chdir(cmd->arg[1]))
	{
		perror("cd");
		g_status.exit_status = 1;
	}
	else
	{
		if (!current)
			current = ft_get_pwd(myenv);
		update_myenv(myenv, "OLDPWD=", current);
		update_myexp(myexp, "OLDPWD=", current);
		update_myenv(myenv, "PWD=", current);
		update_myexp(myexp, "PWD=", current);
		g_status.exit_status = 0;
		current = getcwd(NULL, 0);
		free(current);
	}
}
