/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/31 14:24:42 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <stdbool.h>

/*

   >>	-	archivo
   >	-	archivo
   <	-	archivo
   <<	-	delimitador
   &&	-	comando
   ||	-	comando
   |	-	comando
   $	-	var
   syn	-	comando + argumentos + opciones || nombre_variable=valor

*/

// Quotes:	' -> No hacer expansion ni nada literal
// 			" -> Se hace expansion

// export solo a-z, A-Z, 0-9, '_'
// Si es un heredoc (<<) devolver un line diferente

static void	print_error(char *err)
{
	fd_printf(2, "minishell: syntax error near unexpected token `%s'\n", err);
	g_exit_status = 2;
}

static bool	check_syntaxis(t_token *token)
{
	if (token->type == AND || token->type == OR || token->type == PIPE)
		return (print_error(token->value), true);
	while (token->next)
	{
		if (token->type != WORD && token->next->type != WORD)
			return (print_error(token->next->value), true);
		token = token->next;
	}
	if (token->type != WORD)
		return (print_error(token->value), true);
	return (false);
}

char	*process_command(char *line, t_data data)
{
	t_token	*token;
	//t_cmd	*cmd;

	token = get_tokens(line);
	if (check_syntaxis(token))
		return (free_token(token), line);

	// Expandir variables (no expandir si esta entre comillas simples)
	expand(&token, data);
	// Crear estructura de comandos: Comandos, redirecciones, pipes
	// 		EJ: echo hola | grep h > out.txt
	// 		command - pipe - command - redir - file
	// 		echo hola - - grep h - > - out.txt
	//cmd = split_cmd(token);
	// Ejecutar comandos
	//execute_cmd(cmd);
	// Actualizar exit status
	//update();
	
	return (/*free_command(cmd)*/ free_token(token), line);
}
