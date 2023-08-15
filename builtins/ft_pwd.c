/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:13:56 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/04 12:31:26 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_pwd(t_env *myenv)
{
	while (myenv)
	{
		if (ft_strcmp(myenv->key, "PWD=") == 0)
			return (ft_strdup(myenv->value));
		myenv = myenv->next;
	}
	return (NULL);
}

void	ft_pwd(t_env *myenv)
{
	char	*current;

	current = NULL;
	current = getcwd(NULL, 0);
	if (!current)
	{
		current = ft_get_pwd(myenv);
		if (!current)
			return ;
	}
	printf("%s\n", current);
	g_status.exit_status = 0;
	free(current);
}
