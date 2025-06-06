/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:55:07 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 19:32:03 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdlib.h>

void	free_token(t_token *token)
{
	t_token	*next;

	while (token)
	{
		free(token->value);
		next = token->next;
		free(token);
		token = NULL;
		token = next;
	}
}

void	free_comand(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		free_token(cmd->tokens);
		next = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = next;
	}
}
