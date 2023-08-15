/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toknization.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:06:11 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 00:43:52 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_initialize(char *tmp)
{
	int	i;

	i = 0;
	if (ft_strlen(tmp) == 1)
	{
		if (tmp[i] == '|')
			return (1);
		else if (tmp[i] == '<')
			return (2);
		else if (tmp[i] == '>')
			return (3);
		else if (tmp[i] == ' ')
			return (6);
	}
	else if (ft_strcmp(tmp, ">>") == 0)
		return (4);
	else if (ft_strcmp(tmp, "<<") == 0)
		return (5);
	else if (tmp[i] == '\'')
		return (8);
	else if (tmp[i] == '\"')
		return (7);
	else if (tmp[i] == '$')
		return (9);
	return (10);
}

int	handle_q(char current_char, int *quote, int *quote_s)
{
	if (current_char == '"' || current_char == '\'')
	{
		if (current_char == '"')
			*quote = !(*quote);
		if (current_char == '\'')
			*quote_s = !(*quote_s);
		return (1);
	}
	return (0);
}

int	handle_spaces(char current_char, int quote, int quote_s, int *found)
{
	if (current_char == ' ' && !quote && !quote_s)
	{
		if (!(*found))
		{
			*found = 1;
			return (1);
		}
		return (0);
	}
	return (1);
}

void	remov_space(char *str)
{
	int	quote; 
	int	quote_s;
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0; 
	quote = 0; 
	quote_s = 0;
	found = 0;
	while (str[i])
	{
		if (handle_q(str[i], &quote, &quote_s))
		{
			str[j++] = str[i];
			found = 0;
		}
		else if (handle_spaces(str[i], quote, quote_s, &found))
			str[j++] = str[i];
		if (str[i] != ' ')
			found = 0;
		i++;
	}
	str[j] = '\0';
}
