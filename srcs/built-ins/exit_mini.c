/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:06 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 19:03:05 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"
#include "../../inc/print.h"

static long long int	get_num_exit(char *s, bool *err)
{
	const int		len = ft_strlen(s);
	long long int	number;

	if (len > 20)
	{
		*err = true;
		return (0);
	}
	number = 0;
	*err = ft_atoll(s, &number);
	return (number);
}

static int	convert_num(long long int num)
{
	return (num % 256);
}

int	blt_exit(t_data *data, t_token *cmd)
{
	long long int	num;
	bool			error;
	int				status;

	cmd = cmd->next;
	fd_printf(1, "exit\n");
	data->end = true;
	if (!cmd)
		return (g_exit_status);
	error = false;
	num = get_num_exit(cmd->value, &error);
	if (error)
		return (error_exit("exit", cmd->value, 2), 2);
	if (cmd->next)
	{
		data->end = false;
		return (error_exit("exit", NULL, 1), 1);
	}
	status = convert_num(num);
	return (status);
}
