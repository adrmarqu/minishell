/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:13:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/22 18:47:28 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
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

t_token	*new_token(t_token *prev, t_token *current)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (current)
		token->type = current->type;
	else
		token->type = VOID;
	token->value = NULL;
	token->next = NULL;
	if (prev)
		prev->next = token;
	return (token);
}

static t_token	*set_data_token(char *str, t_token *prev)
{
	t_token	*token;

	token = new_token(prev, NULL);
	if (!token)
		return (fd_printf(2, "Error in malloc\n"), NULL);
	token->type = get_type(str);
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
		return (fd_printf(2, "Error in malloc\n"), NULL);
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
