/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:00:42 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 17:25:07 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/built.h"
#include "../../libft/libft.h"

static int	execute_builtin(t_data *data, t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "cd"))
		return (blt_cd(data, cmd));
	else if (!ft_strcmp(cmd->value, "exit"))
		return (blt_exit(data, cmd));
	else if (!ft_strcmp(cmd->value, "export"))
		return (blt_export(data, cmd));
	else if (!ft_strcmp(cmd->value, "unset"))
		return (blt_unset(data, cmd));
	else if (!ft_strcmp(cmd->value, "echo"))
		return (blt_echo(data, cmd));
	else if (!ft_strcmp(cmd->value, "pwd"))
		return (blt_pwd(data, cmd));
	else if (!ft_strcmp(cmd->value, "env"))
		return (blt_env(data, cmd));
	return (1);
}

int	execute(t_cmd *cmd, t_data *data, int input, int output)
{
	if (isbuiltin(cmd->command->value))
		return (execute_builtin(data, cmd->command));
	(void)input;
	(void)output;
	return (0);
}
