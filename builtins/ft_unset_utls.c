/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:23:30 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/05 17:25:09 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_exp(t_exp *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	ft_unsetexp(t_exp **myexp, char *name)
{
	t_exp	*current;
	t_exp	*to_delete;

	current = *myexp;
	to_delete = NULL;
	if (!ft_strcmp(current->name, name))
	{
		*myexp = (*myexp)->next;
		free_exp(current);
	}
	else
	{
		while (current->next)
		{
			if (ft_strcmp(current->next->name, name) == 0)
			{
				to_delete = current->next;
				current->next = current->next->next;
				free_exp(to_delete); 
			}
			else
				current = current->next;
		}
	}
}

void	ft_unsetenv(t_env **myenv, char *name)
{
	t_env	*current;
	t_env	*to_delete;

	current = *myenv;
	to_delete = NULL;
	if (!ft_strcmp(current->key, name))
	{
		*myenv = (*myenv)->next;
		free_env(current);
	}
	else
	{
		while (current->next)
		{
			if (ft_strcmp(current->next->key, name) == 0)
			{
				to_delete = current->next;
				current->next = current->next->next;
				free_env(to_delete);
			}
			else
				current = current->next;
		}
	}
}
