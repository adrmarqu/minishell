/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:03:05 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/02 17:05:28 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"

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
	int		i;

	split = malloc((count_env(env) + 1) * sizeof(char *));
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
