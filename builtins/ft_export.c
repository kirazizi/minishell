/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:26:42 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 01:55:18 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_part(t_exp **expt, t_var var, t_exc *cmd, int *i)
{
	if (is_var(cmd->arg[*i]))
	{
		if (size_arg(cmd->arg) == 2)
			ft_print_export(*expt, var);
		else
		{
			(*i)++;
			return (5);
		}
	}
	return (0);
}

int	check_in_export(t_exp *myexp, char *name, char *value)
{
	char	*new_name;

	new_name = ft_strjoin(name, "=");
	while (myexp)
	{
		if (ft_strcmp(myexp->name, new_name) == 0 && !value)
			return (3);
		if (ft_strcmp(myexp->name, name) == 0 && !value)
			return (4);
		if (ft_strcmp(myexp->name, name) == 0)
			return (2);
		myexp = myexp->next;
	}
	return (0);
}

void	ft_export_part1(t_exp **expt, t_env **myenv, char *str, char *spr)
{
	char	*name_env;
	char	*name_exp;
	char	*data;
	int		flg;

	flg = check_export(str);
	name_env = get_keylen(str, spr +1);
	name_exp = ft_strdup(name_env);
	data = ft_strdup(spr +1);
	remove_redrc_qts(data);
	if (flg == 1)
	{
		update_export_list(name_exp, data, expt);
		update_env_list(name_env, data, myenv);
	}
	else
	{
		replace_export_list(name_exp, data, expt);
		replace_env_list(name_env, data, myenv);
	}
	g_status.exit_status = 0;
}

int	ft_export_part2(t_exp **expt, char *str, int *i)
{
	char	*name_exp;
	char	*value;
	int		flg;

	name_exp = ft_strdup(str);
	value = NULL;
	flg = check_in_export(*expt, name_exp, value);
	if (flg == 2)
		replace_export_list(name_exp, value, expt);
	else if (flg == 3 || flg == 4)
	{
		(*i)++;
		return (5);
	}
	else
		ft_lstadd_back_exprt(expt, creat_list_expt(name_exp, value));
	g_status.exit_status = 0;
	return (0);
}

void	cmd_export(t_exc *cmd, t_exp **expt, t_env **myenv, t_var var)
{
	char	*spr;
	int		i;

	i = 1;
	while (cmd->arg[i])
	{
		if (var_part(expt, var, cmd, &i) == 5)
			continue ;
		else if (parsing_export(cmd->arg[i]))
		{
			error_pars(cmd->arg[i], &i);
			continue ;
		}
		spr = ft_strchr(cmd->arg[i], '=');
		if (spr)
			ft_export_part1(expt, myenv, cmd->arg[i], spr);
		else
		{
			if (ft_export_part2(expt, cmd->arg[i], &i) == 5)
				continue ;
		}
		i++;
	}
	if (!cmd->arg[1])
		ft_print_export(*expt, var);
}
