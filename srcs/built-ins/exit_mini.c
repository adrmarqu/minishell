/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:06 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 18:44:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"
#include "../../inc/print.h"
#include <limits.h>

/*
	
	exit: mira el primer argumento si es un numero valido mira si hay un siguiente
	si lo hay too many arguments y no sales de bash

	LLONG_MAX

*/

static long long int	get_num_exit(char *s, bool *err)
{
	*err = false;
	(void)s;
	return (255);
}

static int	convert_num(long long int num)
{
	return (num % 256);
}

int blt_exit(t_data *data, t_token *cmd)
{
	long long int	num;
	bool			error;

	cmd = cmd->next;
	data->end = true;
	fd_printf(1, "exit\n");
	if (!cmd)
		return (g_exit_status);
	error = false;
	num = get_num_exit(cmd->value, &error);
	if (error)
		return (error_exit(cmd->value, 2), 2);
	if (cmd->next)
	{
		data->end = false;
		return (error_exit(NULL, 1), 1);
	}
	fd_printf(1, "NUM: %d\n", convert_num(num));
    return (0);
}
