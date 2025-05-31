/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:06:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/31 14:45:03 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

// exp
// Primer caracter: a-z, A-Z, '_'
// Resto: 0-9, a-z, A-Z, '_'

static char	*get_expansion(char *str, t_env *env, t_env *local)
{
	char	*ret;

	// Mirar las comillas
	// Calcular hasta donde
	// Hacer substr
	// Si es expansion pues expandir
	// Guardar en la estructura t_exp
	// Una vez acabado hacer un join de todo

	return (ret);
}

int	expand(t_token **tokens, t_data data)
{
	t_token	*first;
	char	*new_str;
	int		i;

	i = 0;
	while (*tokens)
	{
		new_str = get_expansion((*tokens)->value, data.env, data.local_env);
		if (!new_str)
			return (1);
		free((*tokens)->value);
		(*tokens)->value = new_str;
		if (i++ == 0)
			first = *tokens;
		*tokens = (*tokens)->next;
	}
	*tokens = first;
	return (0);
}
