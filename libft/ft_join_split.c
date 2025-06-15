/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:58:13 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 12:33:51 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_split(char **split)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = ft_splitlen(split);
	if (!split || i == 0)
		return (ft_strdup(""));
	if (i == 1)
		return (ft_strdup(split[0]));
	ret = ft_strdup(split[0]);
	if (!ret)
		return (NULL);
	i = 1;
	while (split[i])
	{
		tmp = ret;
		ret = ft_threejoin(tmp, " ", split[i]);
		free(tmp);
		if (!ret)
			return (NULL);
		i++;
	}
	return (ret);
}
