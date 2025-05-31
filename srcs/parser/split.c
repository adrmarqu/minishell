/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:42:36 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/05/31 12:49:45 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/parser.h"

int	match_in_set(const char *p, const char **set)
{
	int	i;
	int	len;

	i = 0;
	while (set[i])
	{
		len = ft_strlen(set[i]);
		if (ft_strncmp(p, set[i], len) == 0)
			return (len);
		i++;
	}
	return (0);
}

static int	count_tokens(const char *line, const char **set)
{
	const char	*p;
	int			count;
	int			len;
	char		quote;

	p = line;
	count = 0;
	while (*p)
	{
		skip_space(&p);
		if (!*p)
			break ;
		len = match_in_set(p, set);
		if (*p == '\'' || *p == '"')
		{
			quote = *p++;
			skip_quote(&p, quote);
		}
		else if (len)
			p += len;
		else
			skip_word(&p, set);
		count++;
	}
	return (count);
}

static int	process_token(char **tokens, int *count, char **p, const char **set)
{
	skip_space((const char **)p);
	if (!**p)
		return (0);
	if (**p == '\'' || **p == '"')
		add_quote_token(tokens, count, p);
	else if (match_in_set(*p, set))
		add_set_token(tokens, count, p, set);
	else
		add_word_token(tokens, count, p, set);
	return (1);
}

char	**split_tokens(char *line, const char **set)
{
	char	**tokens;
	int		count;
	int		size;
	char	*p;

	count = 0;
	p = line;
	size = count_tokens(line, set);
	tokens = malloc(sizeof(char *) * (size + 1));
	if (!tokens)
		return (NULL);
	while (*p)
		if (!process_token(tokens, &count, &p, set))
			break ;
	tokens[count] = NULL;
	return (tokens);
}
