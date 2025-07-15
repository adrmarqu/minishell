/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:54:17 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 18:59:16 by adrmarqu         ###   ########.fr       */
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

void	error_memory(const char *url)
{
	fd_printf(2, "minishell: memory leak in %s\n", url);
	g_exit_status = 1;
}

void	error_option(const char *built, char option)
{
	fd_printf(2, "minishell: %s: -%c: invalid option\n", built, option);
	g_exit_status = 2;
}

void	error_exit(const char *built, const char *s, int type)
{
	if (type == 1)
		fd_printf(2, "minishell: %s: too many arguments\n", built);
	else if (type == 2)
		fd_printf(2, "minishell: %s: %s: numeric argument required\n", built, s);
	g_exit_status = type;
}
