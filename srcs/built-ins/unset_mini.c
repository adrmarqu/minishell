/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:24 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 18:01:11 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../inc/print.h"
#include "../../inc/free.h"
#include "../../libft/libft.h"

void	delete_var(t_env **envp, char *var)
{
	t_env	*env;
	t_env	*prev;

	env = *envp;
	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
		{
			ft_free_one_env(envp, prev, env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	blt_unset(t_data *data, t_token *cmd)
{
	cmd = cmd->next;
	if (!cmd)
		return (0);
	if (cmd->value[0] == '-' && cmd->value[1])
		return (error_option("unset", cmd->value[1]), 2);
	while (cmd)
	{
		delete_var(&data->env, cmd->value);
		cmd = cmd->next;
	}
	return (0);
}
