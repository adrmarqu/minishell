/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:39:03 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 12:10:31 by adrmarqu         ###   ########.fr       */
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
