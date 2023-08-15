/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:44:05 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 00:51:20 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_insialize_and_signal(void)
{
	g_status.heredoc = 0;
	ft_signal();
}

int	main_error(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	history_and_update_status(t_env *myenv, char *input)
{
	add_history(input);
	update_exit_status(&myenv);
}

int	check_heredoc(char *input)
{
	if (g_status.heredoc)
	{
		free(input);
		return (1);
	}
	return (0);
}

void	ft_prompt(t_env **myenv, t_exp **myexp, t_var *var)
{
	t_token	*token;
	t_exc	*cmd;
	char	*input;

	while (1)
	{
		token = NULL;
		cmd = NULL;
		ft_insialize_and_signal();
		input = readline(RED"$>minishell "DEFAULT);
		if (main_error(input))
			break ;
		else if (ft_strlen(input) > 0)
		{
			history_and_update_status(*myenv, input);
			if (ft_check(&token, input, *myenv, &cmd))
				continue ;
			var->size = size_exc(cmd);
			if (check_heredoc(input))
				continue ;
			execut_main(cmd, myenv, *var, myexp);
		}
		free_end(cmd, token, input);
	}
}
