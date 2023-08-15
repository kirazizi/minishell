/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:30:33 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/05 15:32:05 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_myenv(t_env *myenv, char *var, char *value)
{
	while (myenv)
	{
		if (ft_strcmp(myenv->key, var) == 0)
		{
			free(myenv->value);
			myenv->value = ft_strdup(value);
			break ;
		}
		myenv = myenv->next;
	}
}

void	update_myexp(t_exp *myexp, char *var, char *value)
{
	while (myexp)
	{
		if (ft_strcmp(myexp->name, var) == 0)
		{
			free(myexp->value);
			myexp->value = ft_strdup(value);
			break ;
		}
		myexp = myexp->next;
	}
}

char	*get_myenv(t_env *myenv, char *name)
{
	while (myenv)
	{
		if (ft_strcmp(myenv->key, name) == 0)
		{
			return (myenv->value);
		}
		myenv = myenv->next;
	}
	return (NULL);
}

void	ft_cd_part1(t_exc *cmd, t_env *myenv, t_exp *myexp, char *current)
{
	if (chdir(get_myenv(myenv, "HOME=")))
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
