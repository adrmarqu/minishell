/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:42:48 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/31 12:49:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/parser.h"

void	add_token(char **tokens, int *count, const char *start, int len)
{
	char	*token;
	int		i;

	token = malloc(len + 1);
	i = 0;
	if (!token)
		return ;
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[len] = '\0';
	tokens[(*count)++] = token;
}

void	add_quote_token(char **tokens, int *count, char **p)
{
	char	*start;
	char	quote;

	quote = **p;
	start = (*p)++;
	while (**p && **p != quote)
		(*p)++;
	if (**p)
		(*p)++;
	add_token(tokens, count, start, *p - start);
}

void	add_set_token(char **tokens, int *count, char **p, const char **set)
{
	int	len;

	len = match_in_set(*p, set);
	if (len > 0)
	{
		add_token(tokens, count, *p, len);
		*p += len;
	}
}

void	add_word_token(char **tkns, int *count, char **p, const char **set)
{
	char	*start;

	start = *p;
	while (**p && !ft_isspace(**p) && !match_in_set(*p, set)
		&& **p != '\'' && **p != '"')
		(*p)++;
	add_token(tkns, count, start, *p - start);
}
