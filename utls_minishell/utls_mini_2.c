/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_mini_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:28:48 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 21:53:16 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	checkisvarchar(char str)
{
	if (!str)
		return (0);
	if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
		return (1);
	else if (str == '_')
		return (1);
	else if (str == '?')
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = (void *) malloc(count * (size));
	if (!str)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(str));
	ft_bzero(str, count * size);
	return (str);
}
