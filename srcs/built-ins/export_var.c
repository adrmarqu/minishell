/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:19:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/10 19:16:14 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/built.h"
#include "../../libft/libft.h"

char	*get_var_export(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	return (ft_substr(s, 0, len));
}

char	*get_value_export(char *s, bool *error)
{
	size_t	start;
	size_t	end;
	char	*value;

	start = 0;
	while (s[start] && s[start] != '=')
		start++;
	if (s[start] == '\0')
		return (NULL);
	end = start;
	while (s[end])
		end++;
	value = ft_substr(s, start + 1, end);
	if (!value)
	{
		*error = true;
		return (NULL);
	}
	return (value);
}

bool	is_equal(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (true);
		s++;
	}
	return (false);
}

static bool	set_data_var(t_env **env, char *s)
{
	char	*tmp;
	bool	error;

	error = false;
	tmp = get_var_export(s);
	if (!tmp)
		return (false);
	(*env)->var = tmp;
	tmp = get_value_export(s, &error);
	if (error)
		return (free((*env)->var), false);
	(*env)->value = tmp;
	(*env)->equal = is_equal(s);
	(*env)->next = NULL;
	return (true);
}

int	export_var(t_data *data, char *s)
{
	t_env	*new_var;
	t_env	*curr;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (1);
	if (!set_data_var(&new_var, s))
		return (free(new_var), 1);
	curr = data->env;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new_var;
	return (0);
}
