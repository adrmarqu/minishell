/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:13 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/10 19:20:30 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/print.h"
#include "../../libft/libft.h"
#include "../../inc/built.h"

static void	print_export(t_env *env)
{
	t_env	*smallest;

	smallest = NULL;
	while (42)
	{
		smallest = get_smaller(env, smallest);
		if (!smallest)
			break ;
		fd_printf(1, "declare -x %s", smallest->var);
		if (smallest->equal)
		{
			write(1, "=", 1);
			if (smallest->value)
				fd_printf(1, "\"%s\"", smallest->value);
		}
		write(1, "\n", 1);
	}
}

static bool	check_export(char *s)
{
	if (!ft_isalpha(*s) || *s != '_')
		return (false);
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) || *s != '_')
			return (false);
		s++;
	}
	return (true);
}

bool	export_input(t_data *data, char *s)
{
	if (!it_exist(data, s))
		return (export_var(data, s));
	return (export_modify(data, s, is_append(s)));
}

int	blt_export(t_data *data, t_token *cmd)
{
	int	status;

	cmd = cmd->next;
	if (!cmd)
		return (print_export(data->env), 0);
	if (cmd->value[0] == '-' && cmd->value[1])
		return (error_option("export", cmd->value[1]), 2);
	status = 0;
	while (cmd)
	{
		if (!check_export(cmd->value) && !export_input(data, cmd->value))
			status = 1;
		cmd = cmd->next;
	}
	return (status);
}
