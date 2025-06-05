/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:53:40 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 19:42:01 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/global.h"
#include "../inc/utils.h"

static bool	set_data_struct(t_env **env, char const *str)
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
		return (fd_printf(2, "Envp is void\n"), NULL);
	first = NULL;
	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (fd_printf(2, "Error in malloc\n"), NULL);
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

t_data	*init_data(char **av, char **env)
{
	t_data	*ret;

	ret = malloc(sizeof(t_data));
	if (!ret)
		return (NULL);
	ret->shlvl = get_shlvl();
	ret->program_name = av[0];
	ret->env = init_shell(env);
	ret->local_env = malloc(sizeof(t_env));
	ret->local_env->var = NULL;
	ret->local_env->value = NULL;
	ret->local_env->equal = false;
	ret->local_env->next = NULL;
	ret->end = false;
	if (!ret->env || !ret->local_env)
		return (NULL);
	return (ret);
}
