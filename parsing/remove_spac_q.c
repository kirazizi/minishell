/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spac_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:53:45 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/12 23:09:20 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	removed_q_suit(t_exc **token)
{
	t_exc	*txp;
	int		i;

	txp = *token;
	i = 0;
	while (txp)
	{
		i = -1;
		while (txp->arg && txp->arg[++i])
		{
			txp->arg[i] = removedoublesinglequotes(txp->arg[i]);
		}
		txp = txp->next;
	}
}

void	remove_inside_double_quotes(char *p, char *move, int *i, int *j)
{
	if (p[*i] == '"')
	{
		(*i)++;
		while (p[*i] && p[*i] != '"')
		{
			move[(*j)++] = p[(*i)++];
		}
		if (p[*i] == '"')
			(*i)++;
	}
}

void	remove_inside_single_quotes(char *p, char *move, int *i, int *j)
{
	if (p[*i] == '\'')
	{
		(*i)++;
		while (p[*i] && p[*i] != '\'')
		{
			move[(*j)++] = p[(*i)++];
		}
		if (p[*i] == '\'')
			(*i)++;
	}
}

char	*removedoublesinglequotes(char *p)
{
	int		i;
	int		j;
	int		len;
	char	*move;

	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(p);
	move = (char *)malloc(len + 1);
	if (!move)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(move));
	while (p[i])
	{
		remove_inside_double_quotes(p, move, &i, &j);
		remove_inside_single_quotes(p, move, &i, &j);
		if (p[i] && p[i] != '"' && p[i] != '\'')
			move[j++] = p[i++];
	}
	move[j] = '\0';
	return (move);
}
