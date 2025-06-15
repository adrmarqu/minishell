/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:56:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 12:33:01 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_print_split(char **split)
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
