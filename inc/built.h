/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:47:15 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/06 17:19:15 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "global.h"

int		blt_cd(t_data *data, t_token *cmd);
int		blt_exit(t_data *data, t_token *cmd);
int		blt_pwd(t_data *data, t_token *cmd);
int		blt_echo(t_data *data, t_token *cmd);
int		blt_export(t_data *data, t_token *cmd);
int		blt_unset(t_data *data, t_token *cmd);
int		blt_env(t_data *data, t_token *cmd);

t_env	*get_smaller(t_env *env, t_env *last);
bool	is_append(char *s);
bool it_exist(t_data *data, char *s);
char	*get_var_export(char *s);
char	*get_value_export(char *s, bool *error);
bool    is_equal(char *s);

int	export_var(t_data *data, char *s);
int	export_modify(t_data *data, char *s, bool append);

#endif
