/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 07:55:04 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/05 15:32:26 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_exc *cmd, t_env *myenv, t_exp *myexp)
{
	char	*current;

	current = NULL;
	current = getcwd(NULL, 0);
	if (!cmd->arg[1] || ft_strcmp(cmd->arg[1], "~") == 0)
		ft_cd_part1(cmd, myenv, myexp, current);
	else if (cmd->arg[1][0] == '~' && cmd->arg[1][1])
		ft_cd_part2(cmd, myenv, myexp, current);
	else if (!current && !ft_strcmp(cmd->arg[1], ".."))
		ft_cd_part3(myenv, myexp, cmd, current);
	else if (!current && !ft_strcmp(cmd->arg[1], "."))
		ft_cd_part4(myenv, myexp, cmd, current);
	else
		ft_cd_part5(myenv, myexp, cmd, current);
	free(current);
}
