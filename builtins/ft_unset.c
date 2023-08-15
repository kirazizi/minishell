/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:49:35 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 00:17:39 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing_unset(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' && arg[i + 1])
			return (2);
		if (!is_alpha(arg[0]) || (!is_alpha(arg[i]) && !is_digit(arg[i])))
			return (1);
		i++;
	}
	return (0);
}

void	parcing_tools(t_exc *cmd, int i)
{
	if (parsing_unset(cmd->arg[i]) == 2)
	{
		write(2, "unset: ", 7);
		ft_printf(2, cmd->arg[i], ": invalid option\n\
		unset: usage: unset [-f] [-v] [name ...]\n");
		g_status.exit_status = 2;
	}
	else
	{
		write(2, "unset: ", 7);
		ft_printf(2, cmd->arg[i], ": not a valid identifier\n");
		g_status.exit_status = 1;
	}
}

void	ft_unset(t_exc *cmd, t_env **myenv, t_exp **myexp)
{
	int	i;

	i = 1;
	while (cmd->arg[i])
	{
		if (parsing_unset(cmd->arg[i]))
		{
			parcing_tools(cmd, i);
			i++;
			continue ;
		}
		else
		{
			ft_unsetexp(myexp, cmd->arg[i]);
			cmd->arg[i] = ft_strjoin(cmd->arg[i], "=");
			ft_unsetenv(myenv, cmd->arg[i]);
			ft_unsetexp(myexp, cmd->arg[i]);
			g_status.exit_status = 0;
		}
		i++;
	}
}
