/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:19 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:48:44 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"
#include "../../inc/built.h"

int	update_pwd(t_data *data)
{
	modify_data_ext(data, "PWD", true, ft_strdup(data->pwd));
	if (!data->oldpwd)
		modify_data_ext(data, "OLDPWD", false, NULL);
	else
		modify_data_ext(data, "OLDPWD", true, ft_strdup(data->oldpwd));
	return (0);
}

static bool	isoption(t_token *cmd)
{
	char	*s;

	if (!cmd || !cmd->value)
		return (false);
	s = cmd->value;
	if (s[0] == '-' && s[1])
	{
		if (s[1] == '-' && !s[2])
			return (false);
		return (true);
	}
	return (false);
}

int	blt_pwd(t_data *data, t_token *cmd)
{
	char	*cwd;

	cmd = cmd->next;
	if (isoption(cmd))
		return (error_option("pwd", cmd->value[1]), 2);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (2);
	(void)data;
	fd_printf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
