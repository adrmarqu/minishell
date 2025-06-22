/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:34:22 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/22 19:38:04 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

t_cmd	*split_cmd(t_token *token)
{
	
}

/*

Prioridades: || < && < |

La raiz es el que tiene menor prioridad y el que esta mas a la derecha

tipos de raiz: OR, PIPE, AND, END(no hay raiz es el final)

((a && b) || (c && d)) && e || f | (g && h || i) && j

1-
	cmd = OR
	left = ((a && b) || (c && d)) && e
	right = f | (g && h || i) && j

	- Se ejecuta el lado izquierdo, si da true no se hace el derecho

LEFT = ((a && b) || (c && d)) && e

2-
	cmd = AND
	left = (a && b) || (c && d)
	right = e

	- Se ejecuta el lado izquiedo, si da false no se hace el derecho

3- 
	cmd = OR
	left = a && b
	right = c && d

	- Primero se ejecuta a && b, si falla se ejecuta c && d

4-
	cmd = AND
	left = a
	right = b

5-
	cmd = AND
	left = c
	right = d

RIGHT = f | (g && h || i) && j

- Se ejcuta f y la salida pasa como stdin para g

6- 
	cmd = AND
	left = f | (g && h || i)
	right = j

7-
	cmd = PIPE
	left = f
	right = g && h || i

8- 
	cmd = OR
	left = g && h
	right = i

9-
	cmd = AND
	left = g
	right = h

Ejecutar comandos de mas a la izquierda a derecha

Una vez ejecutado lo pones en NULL

*/
