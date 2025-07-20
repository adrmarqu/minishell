/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:52:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 13:57:58 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	error_token(const char *err);
void	error_close(int error);
void	error_memory(const char *url);
void	error_option(const char *blt, char option);
void	error_exit(const char *blt, const char *s, int type);
void	error_invalid(const char *s);
void	error_chdir(const char *s, const char *err);
