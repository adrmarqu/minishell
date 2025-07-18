/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:26 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 17:26:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"

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
