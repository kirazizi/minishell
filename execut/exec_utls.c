/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:58:00 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 19:41:25 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printf(int fd, char *str, char *err)
{
	write(fd, str, ft_strlen(str));
	write(fd, err, ft_strlen(err));
}

int	check_is_slash(char *arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			if (arg[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_is_executabe(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (1);
	return (0);
}

int	check_is_directory(char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if (dir)
	{
		ft_printf(2, arg, ": is a directory\n");
		exit(126);
	}
	return (1);
}

char	**ft_list_to_char(t_env *myenv)
{
	char	**new_env;
	t_env	*temp;
	int		len;
	int		i;

	len = ft_lstsize(myenv);
	new_env = malloc(sizeof(char *) * len +1);
	if (!new_env)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(new_env));
	temp = myenv;
	i = 0;
	while (temp)
	{
		new_env[i++] = ft_strjoin(temp->key, temp->value);
		temp = temp->next;
	}
	new_env[len - 1] = NULL;
	return (new_env);
}
