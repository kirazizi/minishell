/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:22:52 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 19:43:47 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_exc(t_exc *lst)
{
	t_exc	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

int	ft_lstsize(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back2(t_exc **lst, t_exc *new)
{
	t_exc	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

t_exc	*ft_lstnew(char **argm, int in, int out)
{
	t_exc	*head;

	head = NULL;
	head = malloc(sizeof(t_exc));
	if (!head)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(head));
	head->arg = argm;
	head->fdin = in;
	head->fdout = out;
	head->next = NULL;
	return (head);
}
