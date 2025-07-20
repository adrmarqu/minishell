/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mini.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:12 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:48:19 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/built.h"
#include "../../inc/print.h"
#include <errno.h>

static int	update_internal_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(2, "cd: error retrieving current directory: getcwd: cannot"
			" access parent directories: No such file or directory\n");
		cwd = ft_strjoin(data->pwd, "/.");
		if (!cwd)
			return (error_memory("cd_mini/internal_pwd/join()"), 1);
	}
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = ft_strdup(cwd);
	free(cwd);
	if (!data->pwd)
		return (error_memory("cd_mini/internal_pwd/strdup()"), 1);
	return (0);
}

int	ft_chdir(t_data *data, char *path)
{
	chdir(path);
	if (errno == ENOENT)
		return (error_chdir(path, "No such file or directory"), 1);
	else if (errno == ENOTDIR)
		return (error_chdir(path, "Not a directory"), 1);
	else if (errno == EACCES)
		return (error_chdir(path, "Permission denied"), 1);
	else if (errno == ENAMETOOLONG)
		return (error_chdir(path, "File name too long"), 1);
	else if (errno != 0)
		return (error_chdir(path, "Unexpected error in chdir"), 1);
	if (update_internal_pwd(data))
		return (1);
	update_pwd(data);
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
	else if (type == ERROR_ARG)
		return (error_exit("cd", NULL, 1), 1);
	else if (type == ERROR_OPT)
		return (error_option("cd", cmd->value[1]), 2);
	return (ft_chdir(data, cmd->value));
}
