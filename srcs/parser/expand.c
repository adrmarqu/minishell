/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:06:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/24 13:46:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <dirent.h>

static char	*expand_var(char *str, int *idx, t_data *data)
{
	char	**split;
	char	*ret;
	char	*tmp;

	split = split_var(str, *idx + 1);
	if (!split)
		return (NULL);
	tmp = get_var(split[1], data->env, data->local_env);
	free(split[1]);
	split[1] = tmp;
	*idx += ft_strlen(split[1]);
	ret = ft_threejoin(split[0], split[1], split[2]);
	ft_free_split(split);
	free(str);
	return (ret);
}

static char	*find_var_token(char *str, t_data *data)
{
	int		i;
	int		len;
	bool	simple;

	i = 0;
	len = ft_strlen(str);
	simple = false;
	while (i < len)
	{
		if (str[i] == '\'')
			simple = !simple;
		else if (str[i] == '$' && !simple)
		{
			str = expand_var(str, &i, data);
			if (!str)
				return (NULL);
			len = ft_strlen(str);
		}
		i++;
	}
	return (str);
}

bool	expand(t_token **tokens, t_data *data)
{
	t_token	*first;
	char	*new_str;
	char	*tmp;

	first = *tokens;
	while (*tokens)
	{
		tmp = find_var_token(ft_strdup((*tokens)->value), data);
		if (!tmp)
			return (false);
		new_str = find_wildcard_token(tmp);
		if (!new_str)
			return (false);
		new_str = ft_clean_quotes(new_str);
		free((*tokens)->value);
		(*tokens)->value = new_str;
		*tokens = (*tokens)->next;
	}
	*tokens = first;
	return (true);
}
