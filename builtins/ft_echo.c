/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:20:43 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/12 16:35:46 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_part(t_exc *cmd, int *i, int *newline)
{
	int	j;

	while (cmd->arg[*i] && cmd->arg[*i][0] == '-' && 
	cmd->arg[*i][1] == 'n' && *newline != 2)
	{
		j = 1;
		while (cmd->arg[*i][j])
		{
			if (cmd->arg[*i][j] == 'n')
				j++;
			else
			{
				printf("%s ", cmd->arg[*i]);
				if (*i != 1)
					*newline = 0;
				else
					*newline = 2;
				break ;
			}
		}
		(*i)++;
		if (*newline == 1)
			*newline = 0;
	}
}

void	ft_echo(t_exc *cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (!cmd->arg[i])
		return (printf("\n"), (void)0);
	ft_echo_part(cmd, &i, &newline);
	while (cmd->arg[i])
	{
		printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_status.exit_status = 0;
}
