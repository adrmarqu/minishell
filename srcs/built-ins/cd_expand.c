/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:08:00 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:48:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/built.h"
#include "../../inc/print.h"

static char	*get_home_env(t_data *data)
{
	t_env	*env;

	if (!data || !data->env)
		return (NULL);
	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->var, "HOME"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	cd_home(t_data *data)
{
	char	*path;

	path = get_home_env(data);
	if (!path)
	{
		if (!data->home)
			return (fd_printf(2, "minishell: cd: HOME not set\n"), 1);
		path = data->home;
	}
	return (ft_chdir(data, path));
}

int	cd_expand_home(t_data *data, char *path)
{
	int		status;
	char	*dir;

	if (!path[1])
		return (cd_home(data));
	else if (path[1] && path[1] != '/')
	{
		fd_printf(2, "minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	dir = ft_strjoin(data->home, path + 1);
	if (!dir)
		return (error_memory("cd_expand/cd_expand_home()"), 1);
	status = ft_chdir(data, dir);
	free(dir);
	return (status);
}
