/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:26 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:05:32 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"

int blt_env(t_data *data, t_token *cmd)
{
	printf("Has llegado a env: %s\n", cmd->value);
	(void)data;
	(void)cmd;
    return (0);
}
