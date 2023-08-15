/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suit_remove_s_q.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:08:53 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/12 23:09:35 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_string_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	removewhitespacenodes(t_token *head)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*todelete;

	curr = head;
	prev = NULL;
	while (curr != NULL)
	{
		if (is_string_whitespace(curr->data))
		{
			if (prev == NULL)
				head = curr->next;
			else
				prev->next = curr->next;
			todelete = curr;
			curr = curr->next;
			todelete = NULL;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
