/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:16 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 00:48:38 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	g_status;

int	main(int ac, char **av, char **env)
{
	t_env		*myenv;
	t_exp		*myexp;
	t_var		var;

	myenv = NULL;
	myexp = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	ft_env(&myenv, env, &var);
	update_shell_level(&myenv);
	ft_list_export(myenv, &myexp);
	var.inp = dup(STDIN_FILENO);
	var.outp = dup(STDOUT_FILENO);
	ft_prompt(&myenv, &myexp, &var);
	close(var.inp);
	close(var.outp);
	return (0);
}
