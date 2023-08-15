/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_suite2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 03:40:58 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 07:55:30 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_words(int *i, int *inside_word, int *nw, int *in_quotes)
{
	*i = 0;
	*inside_word = 0;
	*in_quotes = 0;
	*nw = 0;
	*in_quotes = 0;
}

void	suit_words(int *inside_word, int *nw)
{
	if (*inside_word)
	{
		(*nw)++;
		*inside_word = 0;
	}
}

void	inti_ex(int *i, int *j, int *in_quotes)
{
	*in_quotes = 0;
	*i = 0;
	*j = -1;
}
