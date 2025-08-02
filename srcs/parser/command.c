/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/02 17:27:40 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"
#include "../../inc/free.h"

// Si es un heredoc (<<) devolver un line diferente

char	*process_command(char *line, t_data *data)
{
	t_cmd		*cmd;
	t_token		*token;

	token = get_tokens(line);
	if (!token)
		return (line);
	if (!check_syntaxis(token))
		return (ft_free_token(token), line);
	cmd = build_cmd_tree(token);
	if (!cmd)
		return (line);
	g_exit_status = execute_cmd_tree(cmd, data, -1, -1);
	ft_free_command(cmd);
	return (line);
}
