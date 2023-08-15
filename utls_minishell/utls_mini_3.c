/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_mini_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:20:24 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 21:53:56 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_alloc_path(char **out, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ':'))
			i++;
		j = i;
		while (str[i] && (str[i] != ':'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!out[k])
				return (NULL);
			ft_delete_back(&g_status.delete, ft_delete_add(out[k]));
			ft_strfill(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

char	**split_path(char *str)
{
	char	**out;
	int		i;
	int		wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ':' ))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ':'))
			i++;
	}
	out = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(out));
	out = ft_alloc_path(out, str);
	return (out);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d1;
	char	*s1;

	d1 = (char *)dest;
	s1 = (char *)src;
	i = 0;
	if (!d1 && !s1)
		return (0);
	while (i < n)
	{
		d1[i] = s1[i];
		i++;
	}
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	ft_delete_back(&g_status.delete, ft_delete_add(result));
	result[len] = '\0';
	return ((char *)ft_memcpy(result, s, len));
}
