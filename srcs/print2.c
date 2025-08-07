/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:39:03 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:46:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"

void	error_invalid(const char *s)
{
	fd_printf(2, "minishell: export: `%s': not a valid identifier\n", s);
	g_exit_status = 1;
}

void	error_chdir(const char *s, const char *err)
{
	fd_printf(2, "minishell: cd: %s: %s\n", s, err);
	g_exit_status = 1;
}

void	error_not_found(const char *cmd)
{
	fd_printf(2, "minishell: %s: command not found\n", cmd);
	g_exit_status = 127;
}
