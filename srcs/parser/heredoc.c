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
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../inc/parser.h"
#include "../../libft/libft.h"

static void	read_heredoc(char *limit, int fd)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		close(fd);
		exit(0);
	}
	if (!ft_strcmp(line, limit))
	{
		free(line);
		close(fd);
		exit(0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

static void	child_heredoc(char *limit, int pfd[2])
{
	close(pfd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (42)
		read_heredoc(limit, pfd[1]);
}

static int	wait_heredoc(pid_t pid, int pfd[2], int *input)
{
	int	status;

	close(pfd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pfd[0]);
		write(1, "\n", 1);
		g_exit_status = 130;
		return (130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		*input = pfd[0];
		return (0);
	}
	close(pfd[0]);
	return (1);
}

static int	make_heredoc(char *limit, int *input)
{
	int		pfd[2];
	pid_t	pid;
	int		ret;
	void	(*old_sig)(int);

	if (!limit || pipe(pfd) < 0)
		return (perror("minishell"), 1);
	if (*input != -1)
		close(*input);
	*input = -1;
	old_sig = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		close(pfd[0]);
		close(pfd[1]);
		signal(SIGINT, old_sig);
		return (perror("minishell"), 1);
	}
	if (pid == 0)
		child_heredoc(limit, pfd);
	ret = wait_heredoc(pid, pfd, input);
	signal(SIGINT, old_sig);
	return (ret);
}

int	heredoc(t_token *cmd, int *input)
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
			status = make_heredoc(curr->next->value, input);
		curr = curr->next;
	}
	return (status);
}
