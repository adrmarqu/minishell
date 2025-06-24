/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/24 13:48:14 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"

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
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*command;
	t_token_type	op;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

char	**split_tokens(char *line, const char **operators);
char	**split_wildcard(char *str);
char	**split_expand(char *str, int idx);
char	**split_var(char *str, int pos);

t_token	*get_tokens(char *line);
t_token	*new_token(t_token *prev, t_token *current);

void	ft_free_token(t_token *token);
void	ft_free_command(t_cmd *cmd);

bool	expand(t_token **tokens, t_data *data);
bool	is_expansion(const char *str);

int		get_max_depth(t_token *token);

char	*get_var(char *var, t_env *env, t_env *local);
char	*find_wildcard_token(char *str);

bool	is_match(const char *s, char **set);
bool	check_syntaxis(t_token *token);

void	update(int exit);

t_cmd	*build_cmd_tree(t_token *token);
t_cmd	*new_cmd(t_token *root);

#endif
