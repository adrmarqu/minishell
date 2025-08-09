/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:16:23 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/09 18:46:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/print.h"
#include "../inc/free.h"

int	g_exit_status = 0;

int	update_shlvl(t_env *env, char *level)
{
	t_env	*curr;
	char	*lvl;

	if (!level)
		lvl = ft_strdup("1");
	else
		lvl = ft_strdup(level);
	if (!lvl)
		return (error_memory("update_shlvl"), 1);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp("SHLVL", curr->var))
		{
			free(curr->value);
			curr->value = lvl;
			return (0);
		}
		curr = curr->next;
	}
	return (0);
}

static void	read_prompt(t_data *data)
{
	char	*line;

	while (!data->end)
	{
		set_signals(data->level, 2, 0);
		line = readline("minishell> ");
		if (!line)
		{
			fd_printf(1, "exit\n");
			return ;
		}
		if (!ft_isempty(line))
		{
			if (is_closed(line))
				line = process_command(line, data);
		}
		if (line && line[0])
			add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (fd_printf(2, "Error: minishell without arguments"), 1);
	data = init_data(env);
	if (data.end)
		return (fd_printf(2, "Error: failed to iniciate minishell"), 1);
	printf("LEVEL: %d\n", data.level);
	set_signals(data.level, 2, 0);
	read_prompt(&data);
	ft_free_data(&data);
	return (g_exit_status);
}
