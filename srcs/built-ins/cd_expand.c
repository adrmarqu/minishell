/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:08:00 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/16 17:29:03 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/built.h"

static char	*get_home_env(t_data *data)
{
	t_env	*env;

	if (!data || !data->env)
		return (NULL);
	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->var, "HOME"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	cd_home(t_data *data)
{
	char	*path;
   
	path = get_home_env(data);
	if (!path)
	{
		if (!data->home)
			return (fd_printf(2, "minishell: cd: HOME not set\n"), 1);
		path = data->home;
	}
	return (ft_chdir(data, path));
}

int	cd_expand_home(t_data *data, char *path)
{
	(void)data;
	(void)path;
	return (0);
}

int	cd_old(t_data *data)
{
	(void)data;
	return (0);
}
