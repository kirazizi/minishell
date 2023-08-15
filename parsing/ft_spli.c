/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:13:21 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 08:01:47 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_words(char *s, char c)
{
	int	i;
	int	nw;
	int	in_quotes;
	int	inside_word;

	ft_init_words(&i, &inside_word, &nw, &in_quotes);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			in_quotes = !in_quotes;
			inside_word = 1;
		}
		else if (!in_quotes && s[i] == c)
		{
			suit_words(&inside_word, &nw);
		}
		else if (!in_quotes && s[i] != c)
			inside_word = 1;
		i++;
	}
	if (inside_word)
		nw++;
	return (nw);
}

static	int	len_caracter(const char *str, char c)
{
	int	i;
	int	in_quotes;

	in_quotes = 0;
	i = 0;
	while (str[i] && (str[i] != c || in_quotes))
	{
		if (str[i] == '"' || str[i] == '\'')
			in_quotes = !in_quotes;
		i++;
	}
	return (i);
}

static int	execute(char *s, char c, char **str)
{
	int		i;
	int		j;
	int		k;
	int		in_quotes;

	inti_ex(&i, &j, &in_quotes);
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c && !in_quotes)
			i++;
		if (!s[i])
			break ;
		str[++j] = ft_calloc(len_caracter(s + i, c) + 1, sizeof(char));
		if (str[j] == NULL)
			return (-1);
		ft_delete_back(&g_status.delete, ft_delete_add(str[j]));
		while (s[i] && (s[i] != c || in_quotes))
		{
			if (s[i] == '"' || s[i] == '\'')
				in_quotes = !in_quotes;
			str[j][k++] = s[i++];
		}
	}
	return (ft_delete_back(&g_status.delete, ft_delete_add(str)), 0);
}

static	void	free_ab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split_use(char const *s, char c)
{
	char	**str;
	size_t	length;
	int		err;

	if (!s)
		return (NULL);
	length = ft_words((char *)s, c) + 2;
	str = ft_calloc(length, sizeof(char *));
	if (!str)
		return (NULL);
	err = execute((char *)s, c, str);
	if (err == -1)
		return (free_ab(str), NULL);
	return (str);
}
