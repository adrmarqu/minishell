/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:36:51 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/12 19:40:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

void		*init_shell(char **env);
void		handle_signal(int sig);
char		*process_command(char *line, t_data *data);
bool		*init_data(char **av, char **env, t_data *data);

#endif
