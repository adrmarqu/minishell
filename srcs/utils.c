/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:26:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 14:00:54 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/print.h"

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

static bool	quotes(char c, int *level, bool s, bool d)
{
	if (c == '(' && !s && !d)
		(*level)++;
	else if (c == ')' && *level == 0)
		return (true);
	else if (c == ')' && !s && !d)
		(*level)--;
	return (false);
}

bool	is_closed(const char *line)
{
	bool	single;
	bool	q_double;
	int		level;

	single = false;
	q_double = false;
	level = 0;
	while (*line)
	{
		if (*line == '\'' && !q_double)
			single = !single;
		else if (*line == '\"' && !single)
			q_double = !q_double;
		else if (quotes(*line, &level, single, q_double))
			return (error_close(2), false);
		line++;
	}
	if (single || q_double)
		error_close(0);
	else if (level != 0)
		error_close(1);
	return (!single && !q_double && level == 0);
}
