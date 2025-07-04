/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:24:40 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:35:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../libft/libft.h"

char	*get_var(char *var, t_env *env, t_env *local)
{
	size_t	len;

	if (!var)
		return (NULL);
	if (!ft_strncmp(var, "$?", 3))
		return (ft_itoa(g_exit_status));
	var++;
	len = ft_strlen(var);
	while (env)
	{
		if (len == ft_strlen(env->var) && !ft_strncmp(var, env->var, len))
			return (ft_strdup(env->value));
		env = env->next;
	}
	while (local && local->var)
	{
		if (len == ft_strlen(local->var) && !ft_strncmp(var, local->var, len))
			return (ft_strdup(local->value));
		local = local->next;
	}
	return (ft_strdup(""));
}

static char	*get_variable(char *str, int start)
{
	int	len;
	int	i;

	i = start + 1;
	if (!str[i])
		return (ft_strdup("$"));
	else if (str[i] && !ft_isalpha(str[i]) && str[i] != '_')
		return (ft_substr(str, start, 2));
	i++;
	len = 2;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	return (ft_substr(str, start, len));
}

char	**split_var(char *str, int pos)
{
	char	**ret;

	ret = malloc(4 * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_substr(str, 0, pos - 1);
	ret[1] = get_variable(str, pos - 1);
	if (!ret[1])
		return (ft_free_split(ret), NULL);
	pos += ft_strlen(ret[1]);
	ret[2] = ft_substr(str, pos - 1, ft_strlen(str) - pos + 1);
	ret[3] = NULL;
	if (!ret[0] || !ret[2])
		return (ft_free_split(ret), NULL);
	return (ret);
}

bool	is_expansion(const char *str)
{
	int		i;
	bool	ret;
	bool	simple;
	bool	q_double;

	i = 0;
	ret = false;
	simple = false;
	q_double = false;
	while (str[i])
	{
		if (str[i] == '\'' && !q_double)
			simple = !simple;
		else if (str[i] == '\"' && !simple)
			q_double = !q_double;
		else if (str[i] == '/' && !simple && !q_double)
			return (false);
		else if (str[i] == '*' && !simple && !q_double)
			ret = true;
		i++;
	}
	return (ret);
}
