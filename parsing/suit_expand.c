/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suit_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:56:57 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/13 19:58:12 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	suit_ex_quotes(int *i, t_token **token, char **output)
{
	int		start;
	char	*substring;

	start = *i;
	(*i)++;
	while ((*token)->data[*i] && (*token)->data[*i] != '\'')
		(*i)++;
	substring = ft_strndup(&(*token)->data[start], *i - start + 1);
	*output = ft_strjoin(*output, substring);
	free(substring);
	if ((*token)->data[*i] == '\'')
		(*i)++;
}

void	suit_end_ex(char **output, int *i, t_token **token)
{
	*output = ft_strjoin(*output, ft_strndup(&(*token)->data[*i], 1));
	(*i)++;
}

void	suit_check_e(int *i, t_token **token, t_env **env, char **output)
{
	char	*word;
	char	*env_var;

	env_var = NULL;
	word = NULL;
	if (checkisvarchar((*token)->data[*i + 1]) == 0)
	{
		*output = ft_strjoin(*output, ft_strndup(&(*token)->data[*i], 2));
		(*i) += 2;
	}
	else
	{
		word = get_env_from_data(&(*token)->data[*i]);
		if (word[0] == '?')
		{
			env_var = get_env_var("?", *env);
			env_var = ft_strjoin(env_var, word + 1);
		}
		else
			env_var = get_env_var(word, *env);
		*output = ft_strjoin(*output, env_var);
		if (word)
			(*i) += ft_strlen(word) + 1;
	}
}
