/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:45:27 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 23:07:06 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_exc **lst)
{
	t_exc	*tmp;
	int		i;

	while (*lst)
	{
		tmp = *lst;
		i = 0;
		while (tmp->arg[i])
		{
			i++;
		}
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	ft_lstclear2(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst;
		if (tmp->data)
			free(tmp->data);
		lst = lst->next;
		free(tmp);
	}
}

t_leaks	*ft_delete_add(void *delete)
{
	t_leaks	*node;

	node = NULL;
	node = malloc(sizeof(t_leaks));
	if (!node)
		return (NULL);
	node->delete = delete;
	node->next = NULL;
	return (node);
}

void	ft_delete_back(t_leaks **lst, t_leaks *new)
{
	t_leaks	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
