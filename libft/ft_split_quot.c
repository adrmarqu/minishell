/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:23:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 20:05:42 by adrmarqu         ###   ########.fr       */
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

static void	set_quots(char c, bool *simple, bool *duple)
{
	if (c == '\'' && !*duple)
		*simple = !*simple;
	else if (c == '\"' && !*simple)
		*duple = !*duple;
}

static void	init(int (*idx)[3], bool (*q)[2])
{
	(*idx)[0] = -1;
	(*idx)[1] = 0;
	(*idx)[2] = -1;
	(*q)[0] = false;
	(*q)[1] = false;
}

char	**ft_split_quot(char const *s, char c)
{
	char	**r;
	int		idx[3];
	bool	quots[2];

	r = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!r || !s)
		return (0);
	init(&idx, &quots);
	while (++idx[0] <= (int)ft_strlen(s))
	{
		set_quots(s[idx[0]], &quots[0], &quots[1]);
		if ((s[idx[0]] != c || quots[0] || quots[1]) && idx[2] < 0)
			idx[2] = idx[0];
		else if (((s[idx[0]] == c && !quots[0] && !quots[1])
				|| idx[0] == (int)ft_strlen(s)) && idx[2] >= 0)
		{
			r[idx[1]] = ft_make_str(s, idx[2], idx[0]);
			if (!r[idx[1]++])
				return (ft_free_split(r), NULL);
			idx[2] = -1;
		}
	}
	r[idx[1]] = NULL;
	return (r);
}
