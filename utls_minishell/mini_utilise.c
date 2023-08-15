/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utilise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:09:17 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 20:09:41 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoinn(const char *s1, const char *s2)
{
	int		lent;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	lent = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((lent + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(str));
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j++] = '\0';
	free((char *)s1);
	return (str);
}

size_t	ft_strl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tab;
	size_t	lent;

	if (!s)
		return (0);
	lent = ft_strlen(s);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	i = 0;
	tab = malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(tab));
	while (i < len && start < lent)
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == c)
		return ((char *)str + i);
	return (NULL);
}
