/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:40:53 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/23 11:38:15 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*r;

	if (ft_strlen(s) == 0 || start > ft_strlen(s))
		return (ft_strdup("\0"));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	r = ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (0);
	ft_strlcpy(r, s + start, len + 1);
	return (r);
}
