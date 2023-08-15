/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:49:22 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/06 16:50:19 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*creat_list(char *key, char *value)
{
	t_env	*env;

	env = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(env));
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

char	*get_keylen(char *env, char *spr)
{
	char	*new_key;
	size_t	keylen;
	int		i;

	i = 0;
	keylen = spr - env;
	new_key = malloc(sizeof(char) * keylen +1);
	if (!new_key)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(new_key));
	while (env[i])
	{
		if (env[i] == '+' && env[i +1] == '=')
		{
			env[i] = env[i +1];
			keylen--;
		}
		i++;
	}
	ft_strncpy(new_key, env, keylen);
	new_key[keylen] = '\0';
	return (new_key);
}

void	fill_myenv_manual(t_env **myenv, t_var *var, char *key, char *value)
{
	var->is_vis = 1;
	key = ft_strdup("PWD=");
	value = getcwd(NULL, 0);
	ft_lstadd_back(myenv, creat_list(key, value));
	key = ft_strdup("OLDPWD=");
	value = NULL;
	ft_lstadd_back(myenv, creat_list(key, value));
	key = ft_strdup("PATH=");
	value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	ft_lstadd_back(myenv, creat_list(key, value));
	key = ft_strdup("SHLVL=");
	value = ft_strdup("0");
	ft_lstadd_back(myenv, creat_list(key, value));
	key = ft_strdup("_=");
	value = ft_strdup("/usr/bin/env");
	ft_lstadd_back(myenv, creat_list(key, value));
}

void	fill_myenv_auto(t_env **myenv, char **env, t_var *var)
{
	int		i;
	char	*key;
	char	*value;
	char	*spr;

	key = NULL;
	value = NULL;
	i = 0;
	var->is_vis = 0;
	while (env && env[i])
	{
		spr = ft_strchr(env[i], '=');
		if (spr)
		{
			key = get_keylen(env[i], spr +1);
			value = ft_strdup(spr +1);
			ft_lstadd_back(myenv, creat_list(key, value));
		}
		i++;
	}
	ft_lstadd_back(myenv, creat_list(ft_strdup("?="), ft_strdup("0")));
}
