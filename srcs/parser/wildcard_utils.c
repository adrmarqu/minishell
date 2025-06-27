/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:20:16 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/27 17:58:47 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

static bool	has_match(const char *s, char **set, int len)
{
	int		i;
	char	*found;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(set[i], "*", ft_strlen(set[i])))
		{
			found = ft_strstr(s, set[i]);
			if (!found)
				return (false);
			s = found + ft_strlen(set[i]);
		}
		i++;
	}
	return (true);
}

bool	is_match(const char *s, char **set)
{
	int	len;

	if (ft_strncmp(set[0], "*", ft_strlen(set[0]))
		&& ft_strncmp(s, set[0], ft_strlen(set[0])))
		return (false);
	len = ft_splitlen(set);
	if (ft_strncmp(set[len - 1], "*", ft_strlen(set[len - 1]))
		&& ft_strncmp(s, set[len - 1], ft_strlen(set[len - 1])))
		return (false);
	return (has_match(s, set, len));
}
