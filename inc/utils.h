/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:28:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 16:53:57 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "global.h"

int		get_shlvl(void);
bool	is_closed(const char *line);

bool	is_expansion(const char *str);
bool	is_builtin(char *command);
bool	is_match(const char *s, char **set);

char	**tokens_to_split(t_token *token);
char	**env_to_split(t_env *env);

char	*get_path(t_data *data);
int		prepare_execution(t_token *cmd, t_data *data, char **path);

#endif
