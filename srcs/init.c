/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:53:40 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/20 12:47:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"
#include <stdio.h>

bool	set_data_struct(t_env **env, char const *str)
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

void	*init_shell(char **envp)
{
	t_env	*first;
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (!envp || !*envp)
		return (printf("Envp is void\n"), NULL);
	first = NULL;
	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (printf("Error in malloc\n"), NULL);
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
