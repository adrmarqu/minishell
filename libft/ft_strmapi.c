/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:48:09 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/23 11:34:58 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*r;

	if (!s || !f)
		return (NULL);
	r = ft_strdup(s);
	if (!r)
		return (NULL);
	i = 0;
	len = ft_strlen(r);
	while (i < len)
	{
		r[i] = f(i, r[i]);
		i++;
	}
	return (r);
}
