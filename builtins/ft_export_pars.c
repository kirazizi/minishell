/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:45:57 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/12 20:47:56 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
		return (1);
	return (0);
}

int	is_digit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	return (0);
}

int	size_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	is_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	parsing_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (!is_alpha(arg[0]) || (arg[i] == '+' && arg[i +1] != '='))
			return (1);
		if (!is_alpha(arg[i]) && !is_digit(arg[i]) && arg[i] != '+')
			return (1);
		i++;
	}
	return (0);
}
