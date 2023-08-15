/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:08:15 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 22:08:43 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_list(t_token *token)
{
	while (token && token->next)
	{
		if ((token->type == OUT) && ((token->next->type == OUT || \
				token->next->type == IN || token->next->type == APPEND || \
				token->next->type == HEREDOC) || (token->next->type == PIPE)))
			return (1);
		if ((token->type == IN) && ((token->next->type == OUT || \
				token->next->type == IN || token->next->type == APPEND || \
				token->next->type == HEREDOC) || (token->next->type == PIPE)))
			return (1);
		if ((token->type == APPEND) && ((token->next->type == OUT || \
				token->next->type == IN || token->next->type == APPEND || \
				token->next->type == HEREDOC) || (token->next->type == PIPE)))
			return (1);
		if ((token->type == HEREDOC) && ((token->next->type == OUT || \
				token->next->type == IN || token->next->type == APPEND || \
				token->next->type == HEREDOC) || (token->next->type == PIPE)))
			return (1);
		token = token->next;
	}
	return (0);
}
