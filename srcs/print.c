/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:54:17 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/22 12:00:28 by adrmarqu         ###   ########.fr       */
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
	if (error == 0)
		fd_printf(2, "minishell: syntax error quots are not closed\n");
	else if (error == 1)
		fd_printf(2, "minishell: syntax error parenthesis are not closed\n");
	else if (error == 2)
		fd_printf(2, "minishell: syntax error near unexpected token `)'\n");
	g_exit_status = 1;
}
