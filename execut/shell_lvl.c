/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:22:37 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 19:41:37 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait_exit(t_exc *cmd, t_var *var)
{
	while (wait(&g_status.status) != -1)
	{
	}
	if (var->size >= 1 && !is_builtin(cmd))
	{
		if (WIFEXITED(g_status.status))
		{
			g_status.exit_status = WEXITSTATUS(g_status.status);
		}
		else if (WIFSIGNALED(g_status.status))
		{
			if (WTERMSIG(g_status.status) == SIGINT)
			{
				g_status.exit_status = 130;
				printf("\n");
			}
			else if (WTERMSIG(g_status.status) == SIGQUIT)
			{
				g_status.exit_status = 131;
				printf("Quit: 3\n");
			}
		}
	}
}

void	update_shell_level(t_env **myenv)
{
	t_env	*tmp;
	char	*shlvl;
	int		i;

	tmp = *myenv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL="))
		{
			i = ft_atoi(tmp->value);
			shlvl = ft_itoa(i +1);
			free(tmp->value);
			tmp->value = shlvl;
			tmp = tmp->next;
			continue ;
		}
		if (!ft_strcmp(tmp->key, "_="))
		{
			free(tmp->value);
			tmp->value = ft_strdup("/usr/bin/env");
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_exit_status(t_env **myenv)
{
	t_env	*tmp;

	tmp = *myenv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?="))
		{
			free(tmp->value);
			tmp->value = ft_itoa(g_status.exit_status);
			break ;
		}
		tmp = tmp->next;
	}
}
