/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:56:32 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 17:48:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../../libft/libft.h"
#include "../../inc/parser.h"

static char	*expand_wildcard(char **dir, char **parts, char *str)
{
	char	**cnc;
	char	*ret;
	int		i;

	cnc = malloc((ft_splitlen(dir) + 1) * sizeof(char *));
	if (!cnc)
		return (NULL);
	i = 0;
	while (*dir)
	{
		if (is_match(*dir, parts))
		{
			cnc[i] = ft_strdup(*dir);
			if (!cnc[i++])
				return (ft_free_split(cnc), NULL);
		}
		dir++;
	}
	cnc[i] = NULL;
	if (i)
		ret = ft_join_split(cnc);
	else
		ret = ft_strdup(str);
	ft_free_split(cnc);
	return (ret);
}

static int	ft_dirlen(void)
{
	DIR	*dir;
	int	size;

	dir = opendir(".");
	if (!dir)
		return (0);
	size = 0;
	while (42)
	{
		if (!readdir(dir))
			break ;
		size++;
	}
	closedir(dir);
	return (size);
}

static char	**get_files_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**ret;
	int				i;

	ret = malloc((ft_dirlen() + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while (42)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		ret[i] = ft_strdup(entry->d_name);
		if (!ret[i++])
			return (ft_free_split(ret), closedir(dir), NULL);
	}
	ret[i] = NULL;
	closedir(dir);
	return (ret);
}

char	*find_wildcard_token(char *str)
{
	char	**split;
	char	**dir;
	char	*r;

	if (!is_expansion(str))
		return (str);
	split = split_wildcard(str);
	if (!split)
		return (NULL);
	dir = get_files_dir();
	if (!dir)
		return (ft_free_split(split), NULL);
	r = expand_wildcard(dir, split, str);
	ft_free_split(dir);
	ft_free_split(split);
	free(str);
	return (r);
}
