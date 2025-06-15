/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:37:13 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 13:24:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

static void	set_quot(char c, bool *s, bool *d)
{
	if (c == '\'' && !(*d))
		*s = !(*s);
	else if (c == '\"' && !(*s))
		*d = !(*d);
}

static int	count_word_length(char *str)
{
	int		len;
	bool	s;
	bool	d;

	s = false;
	d = false;
	len = 0;
	if (str[len] == '*')
	{
		while (str[len] && str[len] == '*')
			len++;
		return (len);
	}
	while (str[len])
	{
		set_quot(str[len], &s, &d);
		if (str[len] == '*' && !s && !d)
			return (len);
		len++;
	}
	return (len);
}

static int	count_words(char *s)
{
	int		count;
	bool	simple;
	bool	duple;
	int		len;

	count = 0;
	simple = false;
	duple = false;
	while (*s)
	{
		set_quot(*s, &simple, &duple);
		len = count_word_length(s);
		if (len)
			count++;
		s += len;
	}
	return (count);
}

static char	*get_str(char **str)
{
	int		len;
	char	*s;

	len = count_word_length(*str);
	if (**str == '*')
		s = ft_strdup("*");
	else
		s = ft_substr(*str, 0, len);
	*str += len;
	return (s);
}

char	**split_wildcard(char *str)
{
	char	**split;
	int		i;
	bool	simple;
	bool	duple;

	split = malloc((count_words(str) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	simple = false;
	duple = false;
	while (*str)
	{
		set_quot(*str, &simple, &duple);
		if (*str == '*' && !simple && !duple)
			split[i] = get_str(&str);
		else
			split[i] = get_str(&str);
		if (!split[i++])
			return (ft_free_split(split), NULL);
	}
	split[i] = NULL;
	return (split);
}
