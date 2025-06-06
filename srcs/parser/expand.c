/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:06:43 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/06 20:32:30 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

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

char	*expand_simple(char *str, int *init, char c)
{
	int		i;
	char	*ret;

	i = *init;
	while (str[i] && str[i + 1] && str[i + 1] != c)
	{
		str[i] = str[i + 1];
		i++;
	}
	*init = i;
	while (str[i] && str[i + 2])
	{
		str[i] = str[i + 2];
		i++;
	}
	while (str[i])
		str[i++] = '\0';
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

char	*expand_double(char *str, int *init, t_data *data)
{
	int		i;
	char	*ret;

	i = *init + 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			str = expand_var(str, &i, data);
			if (!str)
				return (NULL);
			if (str[i] == '\"')
				break ;
		}
		i++;
	}
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

static char	*expand_vars(char *str, t_data *data)
{
	int		i;
	int		len;
	bool	simple;

	i = 0;
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
		}
		i++;
		len = ft_strlen(str);
	}
	printf("LINE: %s\n", str);
	return (str);
}

int	expand(t_token **tokens, t_data *data)
{
	t_token	*first;
	//char	*new_str;
	char	*tmp;

	first = *tokens;
	while (*tokens)
	{
		tmp = expand_vars(ft_strdup((*tokens)->value), data);
		if (!tmp)
			return (1);

		// Expandir *

		//new_str = expand_card(tmp);
		//free(tmp);
		//if (!new_str)
		//	return (1);

		// Quitar comillas

		free((*tokens)->value);
		//(*tokens)->value = new_str;
		(*tokens)->value = tmp;
		*tokens = (*tokens)->next;
	}
	*tokens = first;
	return (0);
}
