/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:26:57 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/01/15 16:35:51 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned long	len;
	char			*r;

	len = ft_strlen(s1) + 1;
	r = (char *)malloc(len * sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcpy(r, s1, len);
	return (r);
}
