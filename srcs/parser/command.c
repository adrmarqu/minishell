/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:14 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/21 14:22:41 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

// Interpretar: |, <, >, <<, >>, &&, ||, $
// Quotes:	' -> No hacer expansion ni nada literal
// 			" -> Se hace expansion
// Redirecciones:	<, > Redireccion simple
// 					<< heredoc
// 					>> redireccion con append
// Pipes y operadores:	| -> pipe
// 						&&|| -> ejecucion condicional

// export solo a-z, A-Z, 0-9, '_'
// Conseguir un char** con todo separado: ' ', <><<>>, &&, ||, |

t_token	*get_tokens(char *line)
{
	const char	*operators[] = {"&&", "||", "|", "<<", "<", ">>", ">", NULL};
	char		**split;
	t_token		*tokens;

	split = ft_splitset(line, operators);
	if (!split)
		return (fd_printf(2, "Error in malloc\n"), NULL);
	print_split((const char **)split);
	ft_free_split(split);
	tokens = malloc(sizeof(t_token));
	return (tokens);
}

// Si es un heredoc (<<) devolver un line diferente
char	*process_command(char *line)
{
	t_token	*token;
	//t_cmd	cmd;

	// Separar linea en tokens: palabras, comillas, operadores
	token = get_tokens(line);
	// Revisar syntaxis: Que por ejemplo no empiece por &&
	//if (check_syntaxis(token))
	//	return (line);
	// Expandir variables (no expandir si esta entre comillas simples)
	//expand(&token)
	// Crear estructura de comandos: Comandos, redirecciones, pipes
	// 		EJ: echo hola | grep h > out.txt
	// 		command - pipe - command - redir - file
	// 		echo hola - - grep h - > - out.txt
	//cmd = split_cmd(token);
	// Ejecutar comandos
	//execute_cmd(cmd);
	// Actualizar exit status
	//update();
	// Liberar recursos
	//ft_free();
	free(token);
	return (line);
}
