/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:28:16 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 20:51:39 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdbool.h>

extern int	g_exit_status;

typedef struct s_env
{
	char			*var;
	char			*value;
	bool			equal;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int				shlvl;
	char			*program_name;
	t_env			*env;
	t_env			*local_env;
	bool			end;
}	t_data;

typedef struct s_exp
{
	char			*str;
	bool			expansion;
	struct s_exp	*next;
}	t_exp;

#endif
