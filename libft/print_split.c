/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:56:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/19 13:00:29 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	print_split(const char **split)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (split && split[i])
		if (printf("%s\n", split[i++]) == -1)
			status = 1;
	return (status);
}
