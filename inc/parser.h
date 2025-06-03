/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/06/03 20:26:37 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*

   	
	pipe	= |
	and		= &&
 	or		= ||
	in		= <
	out		= >
	heredoc	= <<
	append	= >>
 
*/

# include "global.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	OPEN,
	CLOSE,
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
	t_token			*tokens;
	struct s_cmd	*next;
}	t_cmd;

char	**split_tokens(char *line, const char **operators);

int		match_in_set(const char *p, const char **set);

void	skip_space(const char **p);
void	skip_quote(const char **p, char quote);
void	skip_word(const char **p, const char **set);

void	add_token(char **tokens, int *count, const char *start, int len);
void	add_quote_token(char **tokens, int *count, char **p);
void	add_set_token(char **tokens, int *count, char **p, const char **set);
void	add_word_token(char **tkns, int *count, char **p, const char **set);

t_token	*get_tokens(char *line);

void	free_token(t_token *token);
void	free_command(t_cmd *cmd);

int		expand(t_token **tokens, t_data data);

#endif
