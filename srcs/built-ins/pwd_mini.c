/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:19 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:05:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"

int blt_pwd(t_data *data, t_token *cmd)
{
	printf("Has llegado a pwd: %s\n", cmd->value);
	(void)data;
	(void)cmd;
    return (0);
}
