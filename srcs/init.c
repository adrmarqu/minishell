/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:53:40 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 14:50:55 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/utils.h"
#include "../inc/print.h"
#include "../inc/free.h"

static bool	set_data_struct(t_env **env, char const *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	(*env)->var = ft_substr(str, 0, i);
	(*env)->equal = false;
	if (str[i] == '=')
		(*env)->equal = true;
	if (!str[i] || !str[i + 1])
		(*env)->value = ft_strdup("");
	else
		(*env)->value = ft_strdup(str + i + 1);
	if (!(*env)->var || !(*env)->value)
		return (false);
	return (true);
}

static t_env	*set_env_var(t_env **prev, char *var, char *value, bool equal)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->var = ft_strdup(var);
	if (!env->var)
		return (free(env), NULL);
	env->value = ft_strdup(value);
	if (!env->value)
		return (free(env), free(env->var), NULL);
	env->equal = equal;
	env->next = NULL;
	if (prev)
		(*prev)->next = env;
	return (env);
}

static void	*set_env(void)
{
	t_env	*first;
	t_env	*a;
	t_env	*b;
	char	cwd[1024];
	char	*lvl;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (fd_printf(2, "getcwd() error\n"), NULL);
	first = set_env_var(NULL, "PWD", cwd, true);
	if (!first)
		return (NULL);
	a = set_env_var(&first, "OLDPWD", "", false);
	if (!a)
		return (ft_free_env(first), NULL);
	lvl = ft_itoa(get_shlvl());
	if (!lvl)
		return (fd_printf(2, "itoa failed\n"), ft_free_env(first), NULL);
	b = set_env_var(&a, "SHLVL", lvl, true);
	free(lvl);
	if (!b)
		return (ft_free_env(first), NULL);
	a = set_env_var(&b, "_", "/usr/bin/env", true);
	if (!a)
		return (ft_free_env(first), NULL);
	return ((void *)first);
}

static void	*init_env(char **envp)
{
	t_env	*first;
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (!envp || !*envp)
		return (set_env());
	first = NULL;
	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (error_memory("init/init_env()"), NULL);
		if (!set_data_struct(&tmp, envp[i++]))
			return (NULL);
		if (first == NULL)
			first = tmp;
		else
			env->next = tmp;
		env = tmp;
	}
	env->next = NULL;
	return ((void *)first);
}

t_data	init_data(char **env)
{
	t_data	ret;
	t_env	*find;

	ret.end = false;
	ret.home = NULL;
	ret.pwd = NULL;
	ret.oldpwd = NULL;
	ret.envp = NULL;
	ret.argv = NULL;
	ret.env = init_env(env);
	if (!ret.env)
	{
		ret.end = true;
		return (ret);
	}
	find = ret.env;
	while (find)
	{
		if (!ft_strcmp(find->var, "HOME"))
		{
			ret.home = ft_strdup(find->value);
			return (ret);
		}
		find = find->next;
	}
	return (ret);
}
