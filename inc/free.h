/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:47:33 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 12:46:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "global.h"

void	ft_free_data(t_data *data);
void	ft_free_env(t_env *env);
void	ft_free_token(t_token *token);
void	ft_free_two_tokens(t_token *a, t_token *b);
void	ft_free_command(t_cmd *cmd);
void	ft_free_one_env(t_env **list, t_env *prev, t_env *curr);
void    ft_free_data_split(t_data *data);

#endif
