/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:48:37 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/14 01:55:43 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reopen(void)
{
	char	*tty;
	int		fd;

	tty = ttyname(0);
	if (tty == NULL)
		fd = open(ttyname(1), O_RDONLY);
}

int	check_is_expanded(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	herdoc_upp(char *word, int *fd, int expande, t_env *env)
{
	char	*line;

	line = ft_strdup("");
	while (line)
	{
		line = readline("> ");
		if (!line || g_status.heredoc == 1)
		{
			if (g_status.heredoc == 1)
			{
				free(line);
				close(fd[1]);
				close(fd[0]);
			}
			break ;
		}
		ft_delete_back(&g_status.delete, ft_delete_add(line));
		if (line && !ft_strcmp(word, line))
			break ;
		if (!expande)
			line = expand_heredoc(line, env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
}

int	my_here_doc(t_token **token, t_env *env)
{
	char	*word;
	int		expand;
	int		fd[2];

	expand = 0;
	expand = check_is_expanded((*token)->next->data);
	word = ft_strdup((*token)->next->data);
	remove_redrc_qts(word);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	signal(SIGINT, herdoc_signal_handler);
	if (g_status.heredoc)
		return (close(fd[1]), fd[0]);
	herdoc_upp(word, fd, expand, env);
	reopen();
	close(fd[1]);
	return (fd[0]);
}
