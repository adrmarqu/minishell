/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:20:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 12:45:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/global.h"
#include <stdlib.h>

void	ft_free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->var);
		free(env->value);
		free(env);
		env = next;
	}
}

void	ft_free_one_env(t_env **list, t_env *prev, t_env *curr)
{
	t_env	*next;

	next = curr->next;
	if (!prev)
		*list = next;
	else
		prev->next = next;
	free(curr->var);
	free(curr->value);
	free(curr);
}

void	ft_free_data(t_data *data)
{
	ft_free_env(data->env);
	free(data->pwd);
	free(data->oldpwd);
	free(data->home);
}
