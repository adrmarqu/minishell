/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:12:06 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/02 18:52:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../inc/parser.h"
#include "../../libft/libft.h"

static void	read_heredoc(char *limit)
{
	char	*line;

	line = readline("> ");
	if (!line)
		exit(0);
	else if (!ft_strcmp(line, limit))
	{
		free(line);
		exit(0);
	}
	free(line);
}

static int	make_heredoc(char *limit)
{
	pid_t	pid;
	int		status;

	if (!limit)
		return (1);
	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (42)
			read_heredoc(limit);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	heredoc(t_token *cmd)
{
	int		status;
	t_token	*curr;
	t_redir	type;

	status = 0;
	curr = cmd;
	while (curr && !status)
	{
		type = get_redir_type(curr->value);
		if (type == HEREDOC)
			status = make_heredoc(curr->next->value);
		curr = curr->next;
	}
	return (status);
}
