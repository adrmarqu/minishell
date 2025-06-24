/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:55:07 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/24 14:09:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdlib.h>

void	ft_free_token(t_token *token)
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

void	ft_free_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_free_command(cmd->left);
	ft_free_command(cmd->right);
	ft_free_token(cmd->command);
	free(cmd);
}
