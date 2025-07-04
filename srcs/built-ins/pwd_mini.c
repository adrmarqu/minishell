/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:19 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 18:16:14 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

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

int blt_pwd(t_data *data, t_token *cmd)
{
	char	*cwd;
	//t_env	*env;

	cmd = cmd->next;
	if (isoption(cmd))
		return (error_option("pwd", cmd->value[1]), 2);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (2);
	//{
		//fd_printf(1, "pwd: error retrieving current directory: "
		//		"getcwd: cannot access parent directories: No such "
		//		"file or directory\n");
	//}
	(void)data;
	fd_printf(1, "%s\n", cwd);
	free(cwd);
    return (0);
}
