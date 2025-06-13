/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:56:32 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/13 21:11:50 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../../libft/libft.h"
#include "../../inc/parser.h"

static char	*expand_wildcard(const char **dir, const char **parts, char *str)
{
	char	**cnc;
	char	*ret;
	int		i;

	cnc = malloc((splitlen(dir) + 1) * sizeof(char *));
	if (!cnc)
		return (NULL);
	i = 0;
	while (*dir)
	{
		if (is_match(*dir, parts, str))
		{
			cnc[i] = ft_strdup(*dir);
			if (!cnc[i++])
				return (ft_free_split(cnc), NULL);
		}
		dir++;
	}
	cnc[i] = NULL;
	if (i == 0)
		ret = ft_strdup(str);
	else
		ret = ft_join_split((const char **)cnc);
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
	char	**current_dir;
	char	**parts;
	char	*r;

	if (!is_expansion(str))
		return (str);
	parts = ft_split_quot(str, '*');
	if (!parts)
		return (NULL);
	current_dir = get_files_dir();
	if (!current_dir)
		return (ft_free_split(parts), NULL);
	r = expand_wildcard((const char **)current_dir, (const char **)parts, str);

	int i = 0;
	while (parts && parts[i])
	{
		printf("DIR: %p - %s\n", &parts[i], parts[i]);
		i++;
	}

	return (ft_free_split(current_dir), ft_free_split(parts), free(str), r);
}
