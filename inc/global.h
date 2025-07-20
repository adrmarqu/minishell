/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:28:16 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 14:50:35 by adrmarqu         ###   ########.fr       */
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
	t_env			*env;
	bool			end;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	char			**envp;
	char			**argv;
	char			*line;
}	t_data;

typedef struct s_exp
{
	char			*str;
	bool			expansion;
	struct s_exp	*next;
}	t_exp;

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE,
	AND,
	OR,
	OPEN,
	CLOSE,
	VOID,
	END
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	t_token				*command;
	t_token_type		op;
	struct s_cmd		*left;
	struct s_cmd		*right;
}	t_cmd;

#endif
