/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:15:30 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/19 18:59:35 by adrmarqu         ###   ########.fr       */
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

// < << > >> | || && ( )

/*
	ALL () ALL 
	
	WORD, CLOSE &&|| WORD, DIR, OPEN
	
	WORD, CLOSE | WORD, OPEN
	
	<		WORD
	<<		WORD
	>		WORD
	>>		WORD

*/

bool	check_syntaxis(t_token *token)
{
//	t_token			*curr;
//	t_token_type	prev;
//	t_token_type	next;

//	prev = VOID;
//	curr = token;
	if (!check_first(token))
		return (false);
	//while (curr->next)
	//{
//
//	}
	if (!check_last(token))
		return (false);
	return (true);
}
