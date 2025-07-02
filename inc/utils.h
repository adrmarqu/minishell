/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:28:39 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/05 19:13:07 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

int		get_shlvl(void);
bool	is_closed(const char *line);

bool	is_expansion(const char *str);
bool	isbuiltin(char *command);
bool	is_match(const char *s, char **set);
#endif
