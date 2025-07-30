/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:59:45 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/15 17:27:26 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"

typedef enum e_redir
{
	INPUT,
    OUTPUT,
    APPEND,
    HEREDOC,
    EMPTY,
    ERROR
}	t_redir;

char	**split_tokens(char *line, const char **operators);
char	**split_wildcard(char *str);
char	**split_expand(char *str, int idx);
char	**split_var(char *str, int pos);

t_token	*get_tokens(char *line);
t_token	*new_token(t_token *prev, t_token_type op, char *s);

bool	expand(t_token **tokens, t_data *data);

int		get_max_depth(t_token *token);

char	*get_var(char *var, t_env *env);
char	*find_wildcard_token(char *str);

bool	check_syntaxis(t_token *token);

void	update(int exit);

t_cmd	*build_cmd_tree(t_token *token);
t_cmd	*new_cmd(t_token *copy);

t_token	*strip_outer_parens(t_token *tokens);

int		execute_cmd_tree(t_cmd *cmd, t_data *data, int input, int output);
int		execute(t_cmd *cmd, t_data *data, int input, int output);

int heredoc(t_data *data, t_token *cmd);
int set_redirections(t_token *cmd, int *input, int *output);

#endif
