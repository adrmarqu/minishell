/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:45:18 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 17:45:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clean_quotes(char *str)
{
	char	*r;
	int		i;
	int		j;
	int		n_quotes;

	i = 0;
	n_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			n_quotes++;
		i++;
	}
	r = ft_calloc(ft_strlen(str) - n_quotes + 1, sizeof(char));
	if (!r)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			r[j++] = str[i];
		i++;
	}
	return (free(str), r);
}
