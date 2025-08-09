/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:28:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 17:25:38 by adrmarqu         ###   ########.fr       */
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

void	ft_close_files(int a, int b, bool make_dup);

char	*get_path(t_data *data);
int		prepare_execution(t_token *cmd, t_data *data, char **path);

void	set_signals(int intmode, int quitmode);

void	rl_signal(int sig);
void	ex_signal(int sig);

#endif
