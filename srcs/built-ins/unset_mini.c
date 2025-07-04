/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:24 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:06:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"

int blt_unset(t_data *data, t_token *cmd)
{
	printf("Has llegado a unset: %s\n", cmd->value);
	(void)data;
	(void)cmd;
    return (0);
}
