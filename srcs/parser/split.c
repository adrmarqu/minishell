/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:55:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/01 17:04:20 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

int	is_set(char *line, const char **set)
{
	int	i;

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

int	get_size_tokens(char *line, const char **set)
{
	int		count;
	char	quot;

	count = 0;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (*line == '\0')
			break ;
		if (*line == '\'' || *line == '"')
		{
			quot = (*line)++;
			while (*line != quot)
				line++;
		}

	}
	return (count);
}

char	**split_tokens(char *line, char const **set)
{
	char	**ret;

	ret = ft_calloc((get_size_tokens(line, set) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	return (ret);
}
