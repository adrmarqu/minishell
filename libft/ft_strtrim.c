/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:29:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/23 11:37:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_found(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	size_t	i;
	size_t	first;
	size_t	last;

	first = 0;
	while (s1[first] && ft_found(s1[first], set))
		first++;
	last = ft_strlen(s1);
	while (last > first && ft_found(s1[last - 1], set))
		last--;
	r = (char *)ft_calloc((last - first + 1), sizeof(*s1));
	if (!r)
		return (NULL);
	i = 0;
	while (first < last)
		r[i++] = s1[first++];
	r[i] = 0;
	return (r);
}
