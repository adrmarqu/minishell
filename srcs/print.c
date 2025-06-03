/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:54:17 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 21:04:07 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"

void	error_token(const char *err)
{
	fd_printf(2, "minishell: syntax error near unexpected token `%s'\n", err);
	g_exit_status = 2;
}

void	error_eof(const char *err, char c)
{
	if (c == '\'' || c == '\"')
		fd_printf(2, "minishell: %s `%c'\n", err, c);
	fd_printf(2, "minishell: syntax error: unexpected end of file\n");
	g_exit_status = 2;
}
