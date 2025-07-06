/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:07:57 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/06 17:50:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../libft/libft.h"

t_env	*get_smaller(t_env *env, t_env *last)
{
	t_env	*smallest;

	smallest = NULL;
	while (env)
	{
		if (!last || ft_strcmp(env->var, last->var) > 0)
		{
			if (!smallest || ft_strcmp(env->var, smallest->var) < 0)
				smallest = env;
		}
		env = env->next;
	}
	return (smallest);
}

bool	is_append(char *s)
{
	char	prev;

	while (*s && *s != '=')
	{
		prev = *s;
		s++;
	}
	if (prev == '+' && *s && *s == '=')
		return (true);
	return (false);
}


