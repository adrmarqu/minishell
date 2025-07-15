/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:52:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 17:41:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	error_token(const char *err);
void	error_close(int error);
void	error_memory(const char *url);
void	error_option(const char *built, char option);
void	error_exit(const char *s, int type);
void	error_invalid(const char *s);
