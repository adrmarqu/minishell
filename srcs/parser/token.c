/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:13:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/01 13:00:36 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

static t_token_type	get_type(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
		return (WORD);
	if (!ft_strncmp("|", str, len))
		return (PIPE);
	else if (!ft_strncmp("&&", str, len))
		return (AND);
	else if (!ft_strncmp("||", str, len))
		return (OR);
	else if (!ft_strncmp("<", str, len))
		return (IN);
	else if (!ft_strncmp(">", str, len))
		return (OUT);
	else if (!ft_strncmp("<<", str, len))
		return (HEREDOC);
	else if (!ft_strncmp(">>", str, len))
		return (APPEND);
	else
		return (WORD);
}

static t_token	*set_data_token(char *str, t_token *prev)
{
	t_token			*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (fd_printf(2, "Error in malloc\n"), NULL);
	if (prev)
		prev->next = token;
	token->type = get_type(str);
	token->value = str;
	token->next = NULL;
	return (token);
}

static char **split_tokens(char *line, const char **set)
{
	char	**split;
	char	**split_token;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	split_token = ft_subsplit(split, set);
	ft_free_split(split);
	if (!split_token)
		return (NULL);
	return (split_token);
}

t_token	*get_tokens(char *line)
{
	const char	*operators[] = {"&&", "||", "|", "<<", "<", ">>", ">", NULL};
	char		**split;
	t_token		*ret;
	t_token		*token;
	int			i;

	split = split_tokens(line, operators);
	if (!split)
		return (fd_printf(2, "Error in malloc\n"), NULL);
	print_split((const char **)split);
	i = 0;
	while (split[i])
	{
		token = set_data_token(split[i], token);
		if (!token)
			return (free(split), NULL);
		if (!i)
			ret = token;
		i++;
	}
	free(split);
	return (ret);
}
