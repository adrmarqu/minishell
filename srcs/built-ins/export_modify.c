/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:54:47 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/10 19:22:19 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

static int	modify_data(char **val, bool *equal, char *str)
{
	char	*value;
	bool	error;

	if (!is_equal(str))
		return (0);
	*equal = true;
	error = false;
	value = get_value_export(str, &error);
	if (error)
		return (error_memory("export_modify/modify_data()"), 1);
	free(*val);
	*val = value;
	return (0);
}

int	export_modify(t_data *data, char *s)
{
	t_env	*env;
	char	*var;
	size_t	len;

	env = data->env;
	var = get_var_export(s);
	if (!var)
		return (error_memory("export_modify/export_modify()"), 1);
	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(env->var, var, len))
			return (free(var), modify_data(&env->value, &env->equal, s), 0);
		env = env->next;
	}
	free(var);
	return (1);
}
