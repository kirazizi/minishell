/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:47:05 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/15 18:08:24 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_part(t_env *myenv)
{
	while (myenv)
	{
		if (!ft_strcmp(myenv->key, "PATH=") || !myenv->value)
		{
			myenv = myenv->next;
			continue ;
		}
		if (!ft_strcmp(myenv->key, "?="))
		{
			myenv = myenv->next;
			continue ;
		}
		else
			printf("%s%s\n", myenv->key, myenv->value);
		myenv = myenv->next;
	}
}

void	ft_print_env(t_env *myenv, t_var var)
{
	if (var.is_vis)
		print_env_part(myenv);
	else
	{
		while (myenv)
		{
			if (!ft_strcmp(myenv->key, "?="))
			{
				myenv = myenv->next;
				continue ;
			}
			else
				printf("%s%s\n", myenv->key, myenv->value);
			myenv = myenv->next;
		}
	}
	g_status.exit_status = 0;
}

void	ft_env(t_env **myenv, char **env, t_var *var)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!env[0])
		fill_myenv_manual(myenv, var, key, value);
	else
		fill_myenv_auto(myenv, env, var);
}
