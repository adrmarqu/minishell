/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:19 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:32:02 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"

static bool	isoption(t_token *option)
{
	char	*s;

	if (!option || !option->value)
		return (false);
	s = option->value;
	if (s[0] != '-' || !s[1] || s[1] != 'n')
		return (false);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (false);
		s++;
	}
	return (true);
}

int blt_echo(t_data *data, t_token *cmd)
{
	bool	option;

	cmd = cmd->next;
	option = isoption(cmd);
	if (option)
		cmd = cmd->next;
	while (cmd)
	{
		fd_printf(1, "%s", cmd->value);
		if (cmd->next)
			fd_printf(1, " ");
		cmd = cmd->next;
	}
	if (!option)
		fd_printf(1, "\n");
	data->status = 0;
    return (0);
}
