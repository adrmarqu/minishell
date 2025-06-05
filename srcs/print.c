/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:54:17 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 18:03:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"

void	error_token(const char *err)
{
	fd_printf(2, "minishell: syntax error near unexpected token `%s'\n", err);
	g_exit_status = 2;
}

void	error_close(int error)
{
	if (error)
		fd_printf(2, "minishell: syntax error quots are not closed\n");
	else
		fd_printf(2, "minishell: syntax error parenthesis are not closed\n");
	g_exit_status = 1;
}
