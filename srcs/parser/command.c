/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/24 14:43:54 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

// Si es un heredoc (<<) devolver un line diferente

void	update(int exit)
{
	g_exit_status = exit;
}

char	*process_command(char *line, t_data *data)
{
	t_token	*token;
	t_cmd	*cmd;

	token = get_tokens(line);
	if (!token)
		return (update(2), line);
	if (!check_syntaxis(token))
		return (ft_free_token(token), line);
	cmd = build_cmd_tree(token);
	if (!cmd)
		return (line);
	(void)data;
	//expand(&token, data);
	//expand(&cmd, data);
	//execute_cmd(cmd);
	//update_exit_status();
	ft_free_command(cmd);
	return (line);
}
