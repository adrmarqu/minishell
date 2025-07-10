/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:07:57 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/10 19:22:38 by adrmarqu         ###   ########.fr       */
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

bool	it_exist(t_data *data, char *s)
{
	t_env	*env;
	size_t	len;
	char	prev;

	prev = '0';
	len = 0;
	while (s[len] && s[len] != '=')
	{
		prev = s[len];
		len++;
	}
	if (s[len] && s[len] == '=' && prev == '+')
		len--;
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->var, s, len))
			return (true);
		env = env->next;
	}
	return (false);
}
