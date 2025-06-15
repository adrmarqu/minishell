/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:15:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 19:55:31 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/print.h"
#include <stdlib.h>

static bool	check_first(t_token *token)
{
	while (token && (token->type == OPEN || token->type == CLOSE))
		token = token->next;
	if (!token)
		return (update(0), false);
	if (token->type == PIPE || token->type == OR || token->type == AND)
		return (error_token(token->value), false);
	return (true);
}

static bool	check_last(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type != OPEN && token->type != CLOSE)
			last = token;
		token = token->next;
	}
	if (last->type != WORD)
		return (error_token(token->value), false);
	return (true);
}

bool	check_syntaxis(t_token *token)
{
	t_token			*curr;
	t_token_type	prev;
	t_token_type	next;

	prev = VOID;
	curr = token;
	if (!check_first(token))
		return (false);
	while (curr->next)
	{
		next = curr->next->type;
		if (curr->type == OR || curr->type == AND || curr->type == PIPE)
		{
			if (prev != WORD || next != WORD)
				return (error_token(curr->value), false);
		}
		else if (curr->type == IN || curr->type == OUT
				|| curr->type == APPEND || curr->type == HEREDOC)
		{
			if ((prev != VOID && prev != WORD) || next != WORD)
				return (error_token(curr->value), false);
		}
		else if (curr->type == OPEN)
		{
			if ((prev != OPEN && prev != CLOSE && prev != WORD && prev != VOID)
				|| (next != WORD && next != OPEN && next != CLOSE))
				return (error_token(curr->value), false);
		}
		else if (curr->type == CLOSE)
		{
			if ((prev != OPEN && prev != CLOSE && prev != WORD)
				|| (next != WORD && next != OPEN && next != CLOSE))
				return (error_token(curr->value), false);
		}
		curr = curr->next;
	}
	if (!check_last(token))
		return (false);
	return (true);
}
