/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/20 14:04:10 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// Interpretar: |, <, >, <<, >>, &&, ||, $
// Quotes:	' -> No hacer expansion ni nada literal
// 			" -> Se hace expansion
// Redirecciones:	<, > Redireccion simple
// 					<< heredoc
// 					>> redireccion con append
// Pipes y operadores:	| -> pipe
// 						&&|| -> ejecucion condicional

// Si es un heredoc (<<) devolver un line diferente
char	*process_command(char *line)
{
	t_cmd	cmd;
	t_token	token;
	
	// Separar linea en tokens: palabras, comillas, operadores
	token = get_commands(line);
	// Revisar syntaxis: Que por ejemplo no empiece por &&
	if (check_syntaxis(token))
		return (line);
	// Expandir variables (no expandir si esta entre comillas simples)
	expand(&token)
	// Crear estructura de comandos: Comandos, redirecciones, pipes
	// 		EJ: echo hola | grep h > out.txt
	// 		command - pipe - command - redir - file
	// 		echo hola - - grep h - > - out.txt
	cmd = split_cmd(token);
	// Ejecutar comandos
	execute_cmd(cmd);
	// Actualizar exit status
	uppdate();
	// Liberar recursos
	ft_free();
	
	return (line);
}
