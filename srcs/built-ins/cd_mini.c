/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mini.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 20:54:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../inc/print.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int	ft_chdir(t_data *data, char *path)
{
	printf("PATH: %s\n", path);
	chdir(path);
	if (errno == ENOENT)
		error_chdir(path, "No such file or directory");
	else if (errno == ENOTDIR)
		error_chdir(path, "Not a directory");
	else if (errno == EACCES)
		error_chdir(path, "Permission denied");
	else if (errno == ENAMETOOLONG)
		error_chdir(path, "File name too long");
	else if (errno != 0)
		error_chdir(path, "Unexpected error in chdir");
	//update_pwd(data, path);
	(void)data;
	return (0);
}

static t_type	get_type_cd(t_token *cmd)
{
	char	*s;

	if (!cmd)
		return (HOME);
	s = cmd->value;
	if (s && s[0] == '-' && s[1])
		return (ERROR_OPT);
	if (cmd->next)
		return (ERROR_ARG);
	if (s[0] == '~')
		return (EXP);
	if (s[0] == '-')
		return (OLD);
	return (ROUTE);
}

int	blt_cd(t_data *data, t_token *cmd)
{
	t_type	type;

	cmd = cmd->next;
	type = get_type_cd(cmd);
	if (type == HOME)
		return (cd_home(data));
	else if (type == EXP)
		return (cd_expand_home(data, cmd->value));
	else if (type == OLD)
		return (cd_old(data));
	else if (type == ERROR_ARG)
		return (error_exit("cd", NULL, 1), 1);
	else if (type == ERROR_OPT)
		return (error_option("cd", cmd->value[1]), 2);
	return (ft_chdir(data, cmd->value));
}
