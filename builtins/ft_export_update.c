/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:52:13 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/12 22:24:52 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_list(char *value, t_exp *myexp, int nb)
{
	if (nb == 0)
	{
		value = ft_strjoin("\"", value);
		value = ft_strjoin(value, "\"");
		myexp->value = value;
	}
	else if (nb == 1)
	{
		if (ft_strcmp(value, "") == 0)
		{
			value = ft_strjoin("\"", value);
			value = ft_strjoin(value, "\"");
			value = ft_strjoin("=", value);
		}
		else
		{
			value = ft_strjoin("\"", value);
			value = ft_strjoin(value, "\"");
			value = ft_strjoin("=", value);
		}
		myexp->value = value;
	}
	return (value);
}

void	replace_export_list(char *name, char *value, t_exp **myexp_head)
{
	char	*new_name;
	t_exp	*myexp;
	int		flg;

	myexp = *myexp_head;
	flg = 0;
	new_name = allocat_new_name(name);
	while (myexp)
	{
		if (!ft_strcmp(myexp->name, name))
		{
			value = ft_check_list(value, myexp, 0);
			flg = 1;
			break ;
		}
		else if (!ft_strcmp(myexp->name, new_name))
		{
			value = ft_check_list(value, myexp, 1);
			flg = 1;
			break ;
		}
		myexp = myexp->next;
	}
	if (!flg)
		add_back(myexp_head, name, value);
}

void	replace_env_list(char *name, char *value, t_env **myenv_head)
{
	t_env	*myenv;
	int		flg;

	myenv = *myenv_head;
	flg = 0;
	while (myenv)
	{
		if (ft_strcmp(myenv->key, name) == 0)
		{
			myenv->value = value;
			flg = 1;
			break ;
		}
		myenv = myenv->next;
	}
	if (!flg)
		ft_lstadd_back(myenv_head, creat_list(name, value));
}

void	update_env_list(char *name, char *value, t_env **myenv_head)
{
	t_env	*myenv;
	int		flg;

	myenv = *myenv_head;
	flg = 0;
	while (myenv)
	{
		if (ft_strcmp(myenv->key, name) == 0)
		{
			myenv->value = ft_strjoin(myenv->value, value);
			flg = 1;
			break ;
		}
		myenv = myenv->next;
	}
	if (!flg)
		ft_lstadd_back(myenv_head, creat_list(name, value));
}

void	update_export_list(char *name, char *value, t_exp **myexp_head)
{
	char	*new_name;
	t_exp	*myexp;
	int		flg;

	myexp = *myexp_head;
	flg = 0;
	new_name = allocat_new_name(name);
	while (myexp)
	{
		if (ft_strcmp(myexp->name, name) == 0)
		{
			myexp->value = join_quates(myexp->value, value);
			flg = 1;
			break ;
		}
		else if (ft_strcmp(myexp->name, new_name) == 0)
		{
			myexp->value = join_quates(myexp->value, value);
			flg = 1;
			break ;
		}
		myexp = myexp->next;
	}
	if (!flg)
		add_back(myexp_head, name, value);
}
