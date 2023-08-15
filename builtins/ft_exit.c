/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:10:02 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 00:18:19 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing_exit(char **arg, t_var *var)
{
	int	i;

	i = 0;
	ft_atol(arg[1], var);
	while (arg[1][i])
	{
		if (arg[1][i] == '-' || arg[1][i] == '+')
			i++;
		else if (var->flg_exit == 1 || ft_strlen(arg[1]) > 20)
			return (2);
		else if (!is_digit(arg[1][i]))
			return (2);
		i++;
	}
	if (arg[2])
		return (1);
	return (0);
}

void	ft_exit(t_exc *cmd, t_var *var)
{
	if (!cmd->arg[1])
	{
		printf("exit\n");
		g_status.exit_status = 0;
		exit(0);
	}
	else if (parsing_exit(cmd->arg, var) == 1)
	{
		write(2, "exit: ", 6);
		ft_printf(2, cmd->arg[1], ": too many arguments\n");
		g_status.exit_status = 1;
	}
	else if (parsing_exit(cmd->arg, var) == 2)
	{
		write(2, "exit: ", 6);
		ft_printf(2, cmd->arg[1], ": numeric argument required\n");
		g_status.exit_status = 255;
		exit(255);
	}
	else
	{
		printf("exit\n");
		g_status.exit_status = ft_atol(cmd->arg[1], var) % 256;
		exit(ft_atol(cmd->arg[1], var) % 256);
	}
}
