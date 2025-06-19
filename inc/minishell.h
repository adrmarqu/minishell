/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:36:51 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:01 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

void		*init_shell(char **env);
void		handle_signal(int sig);
char		*process_command(char *line, t_data *data);
t_data		*init_data(char **av, char **env);

void		ft_free_data(t_data *data);
void		ft_free_env(t_env *env);

#endif
