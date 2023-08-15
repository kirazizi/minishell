/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:22:18 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 22:08:39 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_2(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == '\0')
		return (1);
	if (input[*i] == quote)
	{
		(*i)++;
		return (2);
	}
	return (0);
}

int	syntax_quote(char *input)
{
	int	i;
	int	status;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			status = syntax_2(input, &i, '"');
			if (status == 1)
				return (1);
			else if (status == 2)
				continue ;
		}
		if (input[i] == '\'')
		{
			status = syntax_2(input, &i, '\'');
			if (status == 1)
				return (1);
			else if (status == 2)
				continue ;
		}
		i++;
	}
	return (0);
}

int	check_syntax_end(char *input)
{
	int	i;

	i = ft_strlen(input);
	i--;
	while (i > 0 && input[i] == ' ')
		i--;
	if (input[i] == '>')
		return (1);
	if (input[i] == '<')
		return (1);
	return (0);
}

int	syntax_part_2(char *input, int *i)
{
	while (input[*i] == '|')
	{
		(*i)++;
		while (input[*i] == ' ')
			(*i)++;
		if (input[*i] == '|' || input[*i] == ';')
			return (1);
		else
			break ;
	}
	return (0);
}

int	check_syntax(char *input)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	while (input[j] == ' ')
		j++;
	while (input[i])
	{
		if (input[j] == '|')
			return (1);
		if (syntax_part_2(input, &i))
			return (1);
		i++;
	}
	if (input[len -1] == ' ' && (input[len -2] == '|' || input[len -2] == '>'))
		return (1);
	if (input[len -1] == '|' || input[len -1] == '>' || input[len -1] == '<')
		return (1);
	return (0);
}
