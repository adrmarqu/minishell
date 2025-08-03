/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:52:26 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:02:14 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <fcntl.h>

t_redir	get_redir_type(char *line)
{
	if (!ft_strcmp(line, "<"))
		return (INPUT);
	else if (!ft_strcmp(line, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(line, ">>"))
		return (APPEND);
	else if (!ft_strcmp(line, "<<"))
		return (HEREDOC);
	return (EMPTY);
}

static int	set_stdin(char *file, int *input)
{
	int	fd;

	if (!file)
		return (1);
	if (*input != -1)
		close(*input);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (fd_printf(2, "minishell: %s: ", file), perror(""), 1);
	*input = fd;
	return (0);
}

static int	set_stdout(char *file, int *output)
{
	int	fd;

	if (!file)
		return (1);
	if (*output != -1)
		close(*output);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (fd_printf(2, "minishell: %s: ", file), perror(""), 1);
	*output = fd;
	return (0);
}

static int	set_append(char *file, int *output)
{
	int	fd;

	if (!file)
		return (1);
	if (*output != -1)
		close(*output);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (fd_printf(2, "minishell: %s: ", file), perror(""), 1);
	*output = fd;
	return (0);
}

int	set_redirections(t_token *cmd, int *input, int *output)
{
	t_token	*curr;
	t_redir	type;
	int		status;

	status = 0;
	curr = cmd;
	while (curr && !status)
	{
		type = get_redir_type(curr->value);
		if (type == INPUT)
			status = set_stdin(curr->next->value, input);
		else if (type == OUTPUT)
			status = set_stdout(curr->next->value, output);
		else if (type == APPEND)
			status = set_append(curr->next->value, output);
		curr = curr->next;
	}
	return (status);
}
