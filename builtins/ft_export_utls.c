/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:44:11 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/12 20:47:16 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocat_new_name(char *name)
{
	int		len;
	char	*new_name;

	len = ft_strlen(name) -1;
	new_name = malloc(sizeof(char) * len +1);
	if (!new_name)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(new_name));
	new_name[len] = '\0';
	ft_strncpy(new_name, name, len);
	return (new_name);
}

void	add_back(t_exp **myexp, char *name, char *value)
{
	value = ft_strjoin("\"", value);
	value = ft_strjoin(value, "\"");
	ft_lstadd_back_exprt(myexp, creat_list_expt(name, value));
}

void	ft_list_export(t_env *myenv, t_exp **myexp)
{
	char	*key;
	char	*value; 

	while (myenv)
	{
		key = ft_strdup(myenv->key);
		value = ft_strjoin("\"", myenv->value);
		value = ft_strjoin(value, "\"");
		ft_lstadd_back_exprt(myexp, creat_list_expt(key, value));
		myenv = myenv->next;
	}
	sort_list_exp(*myexp);
}

void	ft_lstadd_back_exprt(t_exp **lst, t_exp *new)
{
	t_exp	*last;

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

t_exp	*creat_list_expt(char *name, char *value)
{
	t_exp	*expt;

	expt = NULL;
	expt = malloc(sizeof(t_exp));
	if (!expt)
		return (NULL);
	ft_delete_back(&g_status.delete, ft_delete_add(expt));
	expt->name = name;
	expt->value = value;
	expt->next = NULL;
	return (expt);
}
