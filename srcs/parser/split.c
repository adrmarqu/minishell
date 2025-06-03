/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:55:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 20:13:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

int	is_set(char *line, const char **set)
{
	int		len;
	int		i;

	i = 0;
	while (set[i])
	{
		len = ft_strlen(set[i]);
		if (!ft_strncmp(line, set[i], len))
			return (len);
		i++;
	}
	return (0);
}

// '  Hola << que<<a    <<<<"<<"tal<<<   '
// 'Hola << que << a << << "<<"tal << <'

static int	get_size(char *line, const char **set)
{
	int		i;
	char	quot;

	i = 0;
	while (line[i] && !ft_isspace(line[i]) && !is_set(line + i, set))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quot = line[i++];
			while (line[i] != quot)
				i++;
		}
		i++;
	}
	return (i);
}

char	*get_word(char *line, const char **set)
{
	char	*str;
	int		i;
	int		j;

	i = is_set(line, set);
	if (!i)
		i = get_size(line, set);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	get_num_tokens(char *line, const char **set)
{
	int		num;
	char	*tmp;

	num = 0;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (*line == '\0')
			break ;
		tmp = get_word(line, set);
		if (!tmp)
			return (-1);
		line += ft_strlen(tmp);
		free(tmp);
		num++;
	}
	return (num);
}

char	**split_tokens(char *line, char const **set)
{
	char	**ret;
	int		pos;

	ret = malloc((get_num_tokens(line, set) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	pos = 0;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (*line == '\0')
			break ;
		ret[pos] = get_word(line, set);
		if (!ret[pos])
			return (ft_free_split(ret), NULL);
		line += ft_strlen(ret[pos++]);
	}
	ret[pos] = NULL;
	return (ret);
}
