/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:40:50 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/21 14:46:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*is_set(const char *str, const char **set)
{
	int		i;
	size_t	len;

	i = 0;
	while (set[i])
	{
		len = ft_strlen(set[i]);
		if (ft_strncmp(str, set[i], len) == 0)
			return (set[i]);
		i++;
	}
	return (NULL);
}

static int	count_words(const char *s, const char **set)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s == '\0')
			break ;
		if (is_set(s, set))
		{
			count++;
			s += ft_strlen(is_set(s, set));
		}
		else
			while (*s && !ft_isspace(*s) && !is_set(s, set))
				s++;
	}
	return (count);
}

char	**ft_splitset(char const *s, char const **set)
{
	char		**split;
	int			pos;
	const char	*st;
	const char	*start;

	split = malloc((count_words(s, set) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	pos = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s == '\0')
			break ;
		st = is_set(s, set);
		if (st)
		{
			split[pos] = ft_strndup(st, ft_strlen(st));
			if (split[pos++] == NULL)
				return (ft_free_split(split), NULL);
			s += ft_strlen(st);
		}
		else
		{
			start = s;
			while (*s && !ft_isspace(*s) && !is_set(s, set))
				s++;
			split[pos] = ft_strndup(start, s - start);
			if (split[pos++] == NULL)
				return (ft_free_split(split), NULL);
		}
	}
	split[pos] = NULL;
	return (split);
}
