/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:02:05 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 13:28:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"
#include "../../inc/print.h"
#include <stdlib.h>

t_token	*get_pipe(t_token **token)
{
	t_token	*pipe;
	t_token	*curr;

	pipe = *token;
	curr = *token;
	while (curr && curr->next)
	{
		if (curr->next->type == PIPE)
		{
			*token = curr->next->next;
			free(curr->next->value);
			free(curr->next);
			curr->next = NULL;
			return (pipe);
		}
		curr = curr->next;
	}
	return (pipe);
}

bool	split_pipes(t_cmd **cmd, t_token *token, int size)
{
	t_token		**split;
	int			i;

	split = malloc((size + 1) * sizeof(t_token *));
	if (!split)
		return (error_memory("split_pipes"), false);
	i = 0;
	while (i < size)
		split[i++] = get_pipe(&token);
	split[i] = NULL;
	(*cmd)->pipes = split;
	(*cmd)->op = PIPE;
	return (true);
}
