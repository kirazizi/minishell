/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:22:15 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 13:02:14 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strfill(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*src;
	char	*dst;

	src = (char *)s;
	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(dst));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*src;

	if (s1 && s2)
	{
		src = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!src)
			return (NULL);
		ft_delete_back(&g_status.delete, ft_delete_add(src));
		i = -1;
		while (s1[++i])
			src[i] = s1[i];
		i = -1;
		while (s2[++i])
			src[ft_strlen(s1) + i] = s2[i];
		src[ft_strlen(s1) + i] = '\0';
		return (src);
	}
	return (NULL);
}
