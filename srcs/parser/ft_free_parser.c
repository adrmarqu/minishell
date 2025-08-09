/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:55:07 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 17:30:30 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
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

void	ft_free_two_tokens(t_token *a, t_token *b)
{
	ft_free_token(a);
	ft_free_token(b);
}

void	ft_free_command(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	ft_free_command(cmd->left);
	ft_free_command(cmd->right);
	ft_free_token(cmd->command);
	if (cmd->pipes)
	{
		i = 0;
		while (cmd->pipes[i])
			ft_free_token(cmd->pipes[i++]);
		free(cmd->pipes);
	}
	free(cmd);
}

void	ft_free_data_split(t_data *data)
{
	ft_free_split(data->argv);
	ft_free_split(data->envp);
	data->argv = NULL;
	data->envp = NULL;
}
