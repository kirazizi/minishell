/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_mini_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:50:39 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 21:53:29 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lenght(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_str_itoa(char *str, int n, int len)
{
	while (n > 0)
	{
		str[len] = 48 + (n % 10);
		len--;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = ft_lenght(n);
	str = malloc(sizeof(char) * len +1);
	if (!str)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(str));
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str[len] = '\0';
	str = ft_str_itoa(str, n, len - 1);
	return (str);
}

static int	ft_test(const char *set, char c)
{
	char	*ptr;

	ptr = (char *)set;
	while (*ptr)
	{
		if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		lent;

	i = 0;
	if (s1 == 0)
		return (NULL);
	if (!s1[0])
		return (ft_strdup(""));
	else if (!set)
		return ((char *)s1);
	lent = ft_strlen(s1);
	while (ft_test(set, s1[i]))
		i++;
	while (ft_test(set, s1[lent - 1]) && lent > i)
		lent--;
	return (ft_substr(s1, i, lent - i));
}
