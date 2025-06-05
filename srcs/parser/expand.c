/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:06:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 20:53:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

// Primer caracter: a-z, A-Z, '_'
// Resto: 0-9, a-z, A-Z, '_'

// Comillas dobles ->	trata como caracteres normales todo lo que hay dentro
// 						excepto a $

static char	*expand_simple(char *str, int *init)
{
	int	i;

	i = *init;
	while (str[i] && str[i + 1] && str[i + 1] != '\'')
	{
		str[i] = str[i + 1];
		i++;
	}
	*init = i;
	while (str[i] && str[i + 2])
	{
		str[i] = str[i + 2];
		i++;
	}
	while (str[i])
		str[i++] = '\0';
	return (str);
}

static char	*expand_input(char *str, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	(void)data;
	while (i < len)
	{
		if (str[i] == '\'')
			str = expand_simple(str, &i);
		//else if (str[i] == '\"')
		//	str = expand_double(str, i);
		//else if (str[i] == '$')
		//	str = expand_var(str, i);
		if (!str)
			return (NULL);
		i++;
		len = ft_strlen(str);
		printf("LINE %d: %s\n", i, str);
	}
	return (str);
}

int	expand(t_token **tokens, t_data *data)
{
	t_token	*first;
	char	*new_str;

	first = *tokens;
	while (*tokens)
	{
		new_str = expand_input((*tokens)->value, data);
		if (!new_str)
			return (1);
		free((*tokens)->value);
		(*tokens)->value = new_str;
		*tokens = (*tokens)->next;
	}
	*tokens = first;
	return (0);
}
