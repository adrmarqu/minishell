/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:26:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 21:03:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>

int	get_shlvl(void)
{
	char	*lvlptr;
	int		lvl;

	lvlptr = getenv("SHLVL");
	if (!lvlptr)
		return (1);
	lvl = ft_atoi(lvlptr);
	if (!lvl)
		return (1);
	return (lvl);
}

bool	quotes_are_closed(const char *line, char *token)
{
	bool	single;
	bool	q_double;
	bool	paren;

	single = false;
	q_double = false;
	paren = false;
	while (*line)
	{
		if (*line == '\'' && !q_double)
			single = !single;
		else if (*line == '"' && !single)
			q_double = !q_double;
		else if (*line == '(')
			paren = !paren;
		else if (*line == ')' && paren)
			paren = !paren;
		line++;
	}
	if (single)
		*token = '\'';
	else if (q_double)
		*token = '\"';
	else if (paren)
		*token = '(';
	return (!single && !q_double && !paren);
}
