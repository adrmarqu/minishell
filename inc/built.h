/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:47:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 19:47:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "global.h"

int	blt_cd(t_data *data, t_token *cmd);
int	blt_exit(t_data *data, t_token *cmd);
int	blt_pwd(t_data *data, t_token *cmd);
int	blt_echo(t_data *data, t_token *cmd);
int	blt_export(t_data *data, t_token *cmd);
int	blt_unset(t_data *data, t_token *cmd);
int	blt_env(t_data *data, t_token *cmd);

#endif
