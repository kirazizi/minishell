/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:43:23 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/12 22:09:18 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_qoutes(int *i, char **input, t_token **token)
{
	ft_token_add(token, ft_substr(*input, 0, *i + 1));
	*input += *i + 1;
	*i = 0;
}

void	simple_word(t_token **token, char **input, int *i)
{
	ft_token_add(token, ft_substr(*input, 0, *i));
	*input += *i + 1;
	*i = 0;
}

void	ft_end_of_word(int *i, char **input, t_token **token)
{
	ft_token_add(token, ft_substr(*input, 0, *i + 1));
	*input += *i + 1;
	*i = 0;
}

void	init_my_vars(int *i, int *in_quotes, int *in_quotes_s)
{
	*i = 0;
	*in_quotes = 0;
	*in_quotes_s = 0;
}

void	thecheck_splite(t_token **token, char *input)
{
	int	i;
	int	in_quotes;
	int	in_quotes_s;

	init_my_vars(&i, &in_quotes, &in_quotes_s);
	while (input[i])
	{
		check_qoutes(input[i], &in_quotes, &in_quotes_s);
		if ((in_quotes_s || in_quotes) && (input[i + 1] == '\0'))
			ft_qoutes(&i, &input, token);
		else if ((!in_quotes && !in_quotes_s && input[i] == ' ') || \
		input[i] == '\t')
			simple_word(token, &input, &i);
		else if (!in_quotes && !in_quotes_s && (!ft_strncmp(input + i, "<<", 2) \
		|| !ft_strncmp(input + i, ">>", 2)))
			ft_her_appa(&i, &input, token);
		else if (!in_quotes && !in_quotes_s && (input[i] == '>' || \
		input[i] == '<' || input[i] == '|'))
			ft_in_out(&i, &input, token);
		else if (!in_quotes && !in_quotes_s && input[i + 1] == '\0')
			ft_end_of_word(&i, &input, token);
		else
			i++;
	}
}
