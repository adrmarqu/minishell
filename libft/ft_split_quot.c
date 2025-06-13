/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:23:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/13 18:54:18 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static int	ft_count_words(const char *str, char c)
{
	int		count;
	bool	simple;
	bool	duple;
	bool	word;

	count = 0;
	simple = false;
	duple = false;
	word = false;
	while (*str)
	{
		if (*str == '\'' && !duple)
			simple = !simple;
		else if (*str == '\"' && !simple)
			duple = !duple;
		else if (*str == c && !simple && !duple && word && count++ >= 0)
			word = false;
		else if (*str == c && !simple && !duple && !word)
			word = true;
		str++;
	}
	if (word)
		count++;
	return (count);
}

static char	*ft_make_str(const char *str, int first, int last)
{
	char	*r;
	int		i;

	i = 0;
	r = ft_calloc((last - first + 1), sizeof(char));
	if (!r)
		return (NULL);
	while (first < last)
		r[i++] = str[first++];
	return (r);
}

char	**ft_split_quot(char const *s, char c)
{
	int		i;
	size_t	j;
	int		start;
	char	**r;
	bool	simple;
	bool	duple;

	r = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!r || !s)
		return (0);
	simple = false;
	duple = false;
	i = -1;
	j = 0;
	start = -1;
	while (++i <= (int)ft_strlen(s))
	{
		if (s[i] == '\'' && !duple)
			simple = !simple;
		else if (s[i] == '\"' && !simple)
			duple = !duple;
		else if ((s[i] != c || simple || duple) && start < 0)
			start = i;
		else if (((s[i] == c && !simple && !duple) || (size_t)i == ft_strlen(s)) && start >= 0)
		{
			r[j++] = ft_make_str(s, start, i);
			if (!r[j - 1])
				return (ft_free_split(r), NULL);
			start = -1;
		}
	}
	r[j] = NULL;
	return (r);
}
