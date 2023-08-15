/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:33:14 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 20:03:33 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	part_1(int *i, char *line, t_env **env, char **output)
{
	char	*word;
	char	*env_var;

	env_var = NULL;
	word = NULL;
	if (checkisvarchar(line[*i + 1]) == 0)
	{
		*output = ft_strjoin(*output, ft_strndup(&line[*i], 2));
		(*i) += 2;
	}
	else
	{
		word = get_env_from_data(&line[*i]);
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

char	*get_heredoc(char *input)
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

char	*get_env_heredoc(char *word, t_env *env)
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

char	*expand_heredoc(char *line, t_env *env)
{
	char	*output;
	int		i;

	i = 0;
	output = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			part_1(&i, line, &env, &output);
		else
		{
			output = ft_strjoin(output, ft_strndup(&line[i], 1));
			i++;
		}
	}
	free(line);
	line = output;
	return (output);
}
