/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:23:46 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 15:25:06 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_part1(char *new_value)
{
	new_value = ft_strjoin("\"", new_value);
	new_value = ft_strjoin(new_value, "\"");
	new_value = ft_strjoin("=", new_value);
	return (new_value);
}

char	*join_part2(char *value, char *new_value, int flg)
{
	value = ft_strjoin("\"", value);
	value = ft_strjoin(value, new_value);
	value = ft_strjoin(value, "\"");
	if (flg)
		value = ft_strjoin("=", value);
	return (value);
}

char	*join_quates(char *value, char *new_value)
{
	int	i;
	int	j;
	int	flg;

	i = 0;
	j = 0;
	flg = 0;
	if (!value)
		return (join_part1(new_value));
	else
	{
		while (value[i])
		{
			if (value[i] == '=')
			{
				i++;
				flg++;
			}
			if (value[i] != '"')
				value[j++] = value[i];
			i++;
		}
		value[j] = '\0';
		return (join_part2(value, new_value, flg));
	}
}
