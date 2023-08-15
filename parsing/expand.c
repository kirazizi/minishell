/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaouh <aennaouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:13:13 by aennaouh          #+#    #+#             */
/*   Updated: 2023/08/12 18:58:52 by aennaouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_prev(t_token *token)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = token;
	if (tmp == NULL)
	{
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*get_env_from_data(char *input)
{
	int		first_i;
	char	*output;
	int		i;

	i = 0;
	first_i = ++i;
	while (input[i] && input[i] != '$' && input[i] != '"' && \
	input[i] != ' ' && input[i] != '\'')
		i++;
	output = ft_strndup(&input[first_i], i - 1);
	return (output);
}

char	*get_env_var(char *word, t_env *env)
{
	char	*tmp_env_key;

	while (env)
	{
		tmp_env_key = ft_substr(env->key, 0, ft_strlen(env->key) - 1);
		if (tmp_env_key && ft_strcmp(word, tmp_env_key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*ft_check_e(t_token **token, t_env *env)
{
	char	*output;
	int		i;

	i = 0;
	output = ft_strdup("");
	if ((*token)->data[i] == '\'' || (*token)->is_input == 1)
		return ((*token)->data);
	while ((*token)->data[i])
	{
		if ((*token)->data[i] == '\'')
		{
			suit_ex_quotes(&i, token, &output);
			continue ;
		}
		if ((*token)->data[i] == '$' && (*token)->data[i + 1])
			suit_check_e(&i, token, &env, &output);
		else
			suit_end_ex(&output, &i, token);
	}
	free((*token)->data);
	(*token)->data = output;
	return (output);
}
