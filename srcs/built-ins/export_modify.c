/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:54:47 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:49:11 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

int	modify_data_ext(t_data *data, const char *var, bool eq, char *val)
{
	t_env	*env;

	if (!val)
		return (1);
	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
		{
			env->equal = eq;
			free(env->value);
			env->value = val;
			return (0);
		}
		env = env->next;
	}
	return (1);
}

static int	modify_data(char **val, bool *equal, char *str)
{
	char	*value;
	bool	error;

	if (!is_equal(str))
		return (0);
	error = false;
	value = get_value_env(str, &error);
	if (error)
		return (error_memory("export_modify/modify_data()"), 1);
	free(*val);
	*val = value;
	*equal = true;
	return (0);
}

static int	add_data(char **val, bool *equal, char *str)
{
	char	*value;
	char	*new_value;
	bool	error;

	error = false;
	value = get_value_env(str, &error);
	if (error)
		return (error_memory("export_modify/add_data()"), 1);
	new_value = ft_strjoin(*val, value);
	free(value);
	if (!new_value)
		return (error_memory("export_modify/add_data()"), 1);
	free(*val);
	*val = new_value;
	*equal = true;
	return (0);
}

int	export_modify(t_data *data, char *s, bool append)
{
	t_env	*env;
	char	*var;
	size_t	len;

	env = data->env;
	var = get_var_env(s);
	if (!var)
		return (error_memory("export_modify/export_modify()"), 1);
	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(env->var, var, len))
		{
			free(var);
			if (!append)
				return (modify_data(&env->value, &env->equal, s));
			else
				return (add_data(&env->value, &env->equal, s));
		}
		env = env->next;
	}
	return (free(var), 1);
}
