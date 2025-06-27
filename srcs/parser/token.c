/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:13:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/27 18:01:50 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include "../../libft/libft.h"

static t_token_type	get_type(const char *str)
{
	const int	len = ft_strlen(str);

	if (!ft_strncmp("|", str, len))
		return (PIPE);
	else if (!ft_strncmp("&&", str, len))
		return (AND);
	else if (!ft_strncmp("||", str, len))
		return (OR);
	else if (!ft_strncmp("<", str, len))
		return (REDIR);
	else if (!ft_strncmp(">", str, len))
		return (REDIR);
	else if (!ft_strncmp("<<", str, len))
		return (REDIR);
	else if (!ft_strncmp(">>", str, len))
		return (REDIR);
	else if (!ft_strncmp("(", str, len))
		return (OPEN);
	else if (!ft_strncmp(")", str, len))
		return (CLOSE);
	else
		return (WORD);
}

int	get_max_depth(t_token *token)
{
	int	depth;
	int	max;

	if (!token)
		return (-1);
	max = 0;
	depth = 0;
	while (token)
	{
		if (token->type == OPEN)
			depth++;
		else if (token->type == CLOSE)
			depth--;
		if (depth > max)
			max = depth;
		token = token->next;
	}
	return (max);
}

static t_token	*set_data_token(char *str, t_token *prev)
{
	t_token	*token;

	token = new_token(prev, get_type(str), NULL);
	if (!token)
		return (error_memory("token/set_data_token()"), NULL);
	token->value = str;
	return (token);
}

t_token	*get_tokens(char *line)
{
	const char	*op[] = {"&&", "||", "|", "<<", "<", ">>", ">", "(", ")", NULL};
	char		**split;
	t_token		*ret;
	t_token		*token;
	int			i;

	split = split_tokens(line, op);
	if (!split)
		return (error_memory("token/get_tokens()"), NULL);
	i = 0;
	token = NULL;
	while (split[i])
	{
		token = set_data_token(split[i], token);
		if (!token)
			return (free(split), ft_free_token(ret), NULL);
		if (!i)
			ret = token;
		i++;
	}
	free(split);
	return (ret);
}
