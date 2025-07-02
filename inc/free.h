#ifndef FREE_H
# define FREE_H

# include "global.h"

void		ft_free_data(t_data *data);
void		ft_free_env(t_env *env);
void        ft_free_token(t_token *token);
void	    ft_free_two_tokens(t_token *a, t_token *b);
void	    ft_free_command(t_cmd *cmd);

#endif