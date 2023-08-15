/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:44:56 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/12 22:09:28 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_qoutes(char c, int *in_quotes, int *in_quotes_s)
{
	if (c == '"' || c == '\'')
	{
		if (c == '"')
			*in_quotes = !(*in_quotes);
		else
			*in_quotes_s = !(*in_quotes_s);
	}
}

void	ft_her_appa(int *i, char **input, t_token **token)
{
	if (*i > 0)
	{
		ft_token_add(token, ft_substr(*input, 0, *i));
	}
	ft_token_add(token, ft_substr(*input, *i, 2));
	*input += *i + 2;
	*i = 0;
}

void	ft_in_out(int *i, char **input, t_token **token)
{
	if (*i > 0)
	{
		ft_token_add(token, ft_substr(*input, 0, *i));
	}
	ft_token_add(token, ft_substr(*input, *i, 1));
	*input += *i + 1;
	*i = 0;
}
