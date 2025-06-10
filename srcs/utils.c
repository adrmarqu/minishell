/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:26:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/10 19:46:03 by adrmarqu         ###   ########.fr       */
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
		else if (*line == '(' && !single && !q_double)
			level++;
		else if (*line == ')' && !single && !q_double)
			level--;
		line++;
	}
	if (single || q_double)
		error_close(true);
	if (level != 0)
		error_close(false);
	return (!single && !q_double && level == 0);
}
