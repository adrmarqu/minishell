/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:48 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 16:54:58 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/print.h"
#include "../../inc/utils.h"

bool	is_builtin(char *command)
{
	int			i;
	const int	len = ft_strlen(command);
	const char	*builtins[] = {"cd", "exit", "export", "unset", "echo",
		"pwd", "env", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], command, len))
			return (true);
		i++;
	}
	return (false);
}

static char	*get_path_env(t_env *data)
{
	t_env	*env;

	env = data;
	while (env)
	{
		if (!ft_strcmp(env->var, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_path(t_data *data)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(get_path_env(data->env), ':');
	s_cmd = ft_split(data->argv[0], ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_split(allpath), ft_free_split(s_cmd), exec);
		free(exec);
	}
	ft_free_split(allpath);
	ft_free_split(s_cmd);
	return (NULL);
}

int	prepare_execution(t_token *cmd, t_data *data, char **path)
{
	*path = NULL;
	data->argv = tokens_to_split(cmd);
	if (!data->argv)
		return (error_memory("execute_utils/prepate_execution/token"), 1);
	data->envp = env_to_split(data->env);
	if (!data->envp)
	{
		ft_free_split(data->argv);
		return (error_memory("execute_utils/prepate_execution/env"), 1);
	}
	*path = get_path(data);
	return (0);
}
