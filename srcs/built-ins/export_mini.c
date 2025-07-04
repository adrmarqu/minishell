/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:13 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:05:49 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"

int blt_export(t_data *data, t_token *cmd)
{
	printf("Has llegado a export: %s\n", cmd->value);
	(void)data;
	(void)cmd;
    return (0);
}
