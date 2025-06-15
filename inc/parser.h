/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/15 19:27:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"

typedef enum e_token_type
{
	WORD,		// Comando o argumento
	PIPE,		// |
	AND,		// &&
	OR,			// ||
	IN,			// <
	OUT,		// >
	HEREDOC,	// <<
	APPEND,		// >> 
	OPEN,		// (
	CLOSE,		// )
	VOID		// void
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*tokens;
	struct s_cmd	*next;
}	t_cmd;

char	**split_tokens(char *line, const char **operators);
char	**split_wildcard(char *str);
char	**split_expand(char *str, int idx);
char	**split_var(char *str, int pos);

t_token	*get_tokens(char *line);

void	free_token(t_token *token);
void	free_command(t_cmd *cmd);

int		expand(t_token **tokens, t_data *data);

char	*get_var(char *var, t_env *env, t_env *local);
bool	is_expansion(const char *str);

char	*find_wildcard_token(char *str);

bool	is_match(const char *s, char **set);
bool	check_syntaxis(t_token *token);
void	update(int exit);

#endif
