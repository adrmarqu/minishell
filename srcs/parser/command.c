/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 20:28:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"


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

char	*process_command(char *line, t_data *data)
{
	t_token	*token;
	//t_cmd	*cmd;

	token = get_tokens(line);
	if (!token)
		return (line);
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

	return (/*free_command(cmd)*/ line);
}
