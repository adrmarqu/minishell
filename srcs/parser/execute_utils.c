/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:48 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 14:55:33 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/global.h"

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

static int	count_tokens(t_token *obj)
{
	t_token	*first;
	int		size;

	first = obj;
	size = 0;
	while (obj)
	{
		obj = obj->next;
		size++;
	}
	obj = first;
	return (size);
}

static int	count_env(t_env *obj)
{
	t_env	*first;
	int		size;

	first = obj;
	size = 0;
	while (obj)
	{
		obj = obj->next;
		size++;
	}
	obj = first;
	return (size);
}

char	**tokens_to_split(t_token *token)
{
	char	**split;
	char	*str;
	int		size;
	int		i;

	size = count_tokens(token);
	split = malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (token)
	{
		str = ft_strdup(token->value);
		if (!str)
		{
			split[i] = NULL;
			return (ft_free_split(split), NULL);
		}
		split[i++] = str;
		token = token->next;
	}
	split[i] = NULL;
	return (split);
}

char	**env_to_split(t_env *env)
{
	char	**split;
	char	*str;
	int		size;
	int		i;

	size = count_env(env);
	split = malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->equal)
			str = ft_threejoin(env->var, "=", env->value);
		else
			str = ft_strdup(env->var);
		if (!str)
		{
			split[i] = NULL;
			return (ft_free_split(split), NULL);
		}
		split[i++] = str;
		env = env->next;
	}
	split[i] = NULL;
	return (split);
}

static char *get_path_env(t_env *data)
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
//get_path(data->env, data->argv[0], data->envp)
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
			return (ft_free_split(s_cmd), exec);
		free(exec);
	}
	ft_free_split(allpath);
	ft_free_split(s_cmd);
	return (data->argv[0]);
}