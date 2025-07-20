/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:26 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:01:19 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"

t_env	*get_env_var(t_data *data, const char *var)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	blt_env(t_data *data, t_token *cmd)
{
	t_env	*env;

	cmd = cmd->next;
	env = data->env;
	while (env)
	{
		if (env->equal)
		{
			fd_printf(1, "%s=", env->var);
			if (env->value)
				fd_printf(1, "%s", env->value);
			fd_printf(1, "\n");
		}
		env = env->next;
	}
	return (0);
}
