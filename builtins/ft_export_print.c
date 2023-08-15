/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:50:39 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/15 18:08:42 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_pars(char *str, int *i)
{
	write(2, "export: `", 9);
	ft_printf(2, str, " : not a valid identifier\n");
	g_status.exit_status = 1;
	(*i)++;
}

int	check_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	sort_list_exp(t_exp *export)
{
	t_exp	*tmp;
	char	*name;
	char	*value;

	while (export)
	{
		tmp = export->next;
		while (tmp)
		{
			if (ft_strcmp(export->name, tmp->name) > 0)
			{
				name = export->name;
				value = export->value;
				export->name = tmp->name;
				export->value = tmp->value;
				tmp->name = name;
				tmp->value = value;
			}
			tmp = tmp->next;
		}
		export = export->next;
	}
}

void	ft_print_1(t_exp *temp)
{
	while (temp)
	{
		if (!ft_strcmp(temp->name, "PATH=") || !ft_strcmp(temp->name, "?=")
			|| !ft_strcmp(temp->name, "_="))
		{
			temp = temp->next;
			continue ;
		}
		if (!ft_strcmp(temp->name, "OLDPWD=") && !temp->value)
		{
			printf("declare -x %s\n", "OLDPWD");
			temp = temp->next;
			continue ;
		}
		if (temp->value)
			printf("declare -x %s%s\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
}

void	ft_print_export(t_exp *exp, t_var var)
{
	t_exp	*temp;

	temp = exp;
	sort_list_exp(temp);
	if (var.is_vis)
		ft_print_1(temp);
	else
	{
		while (temp)
		{
			if (!ft_strcmp(temp->name, "?="))
			{
				temp = temp->next;
				continue ;
			}
			if (temp->value)
				printf("declare -x %s%s\n", temp->name, temp->value);
			else
				printf("declare -x %s\n", temp->name);
			temp = temp->next;
		}
	}
	g_status.exit_status = 0;
}
