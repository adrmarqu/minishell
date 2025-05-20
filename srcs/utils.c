/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:26:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/20 13:56:13 by adrmarqu         ###   ########.fr       */
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

bool	quotes_are_closed(const char *line)
{
	bool	single;
	bool	q_double;

	single = false;
	q_double = false;
	while (*line)
	{
		if (*line == '\'' && !q_double)
			single = !single;
		else if (*line == '"' && !single)
			q_double = !q_double;
		line++;
	}
	return (!single && !q_double);
}
