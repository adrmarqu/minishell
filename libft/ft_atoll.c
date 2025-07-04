/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:26:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 19:43:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <limits.h>

static bool	check_size(__int128 nbr)
{
	if (nbr > LLONG_MAX || nbr < LLONG_MIN)
		return (true);
	return (false);
}

int	ft_atoll(const char *str, long long int *num)
{
	__int128	res;
	short		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	while (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		res = res * 10 + (*str - '0');
		str++;
	}
	res = res * sign;
	if (check_size(res))
		return (1);
	*num = res;
	return (0);
}
