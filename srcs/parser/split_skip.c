/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:39:26 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/31 12:47:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

void	skip_space(const char **p)
{
	while (**p && ft_isspace(**p))
		(*p)++;
}

void	skip_quote(const char **p, char quote)
{
	while (**p && **p != quote)
		(*p)++;
	if (**p == quote)
		(*p)++;
}

void	skip_word(const char **p, const char **set)
{
	while (**p && !ft_isspace(**p) && !match_in_set(*p, set)
		&& **p != '\'' && **p != '"')
		(*p)++;
}
