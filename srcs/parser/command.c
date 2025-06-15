/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 19:49:40 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"


/*

	Command[optional] > file
	Command[optional] >> file
	Command[optional] < file
	Command[optional] << delimitador
	Command | Command
	command || Command
	command && Command

*/

// export solo a-z, A-Z, 0-9, '_'
// Si es un heredoc (<<) devolver un line diferente

void	update(int exit)
{
	g_exit_status = exit;
}

char	*process_command(char *line, t_data *data)
{
	t_token	*token;
	//t_cmd	*cmd;

	token = get_tokens(line);
	if (!token)
		return (line);
	if (check_syntaxis(token))
		return (error_token("ERROR"), line);
	//cmd = split_cmd(token);
	expand(&token, data);
	free_token(token);
	//expand(&cmd, data);
	//execute_cmd(cmd);
	//update_exit_status();
	//free_command(cmd);
	return (line);
}
