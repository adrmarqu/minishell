/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:13:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 20:27:47 by adrmarqu         ###   ########.fr       */
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
	else if (!ft_strncmp("(", str, len))
		return (OPEN);
	else if (!ft_strncmp(")", str, len))
		return (CLOSE);
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

t_token	*get_tokens(char *line)
{
	const char	*op[] = {"&&", "||", "|", "<<", "<", ">>", ">", "(", ")", NULL};
	char		**split;
	t_token		*ret;
	t_token		*token;
	int			i;

	split = split_tokens(line, op);
	if (!split)
		return (fd_printf(2, "Error in malloc\n"), NULL);
	print_split((const char **)split);
	i = 0;
	token = NULL;
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
