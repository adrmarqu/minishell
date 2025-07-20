/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:16:23 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/20 12:45:50 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../inc/global.h"
#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/print.h"
#include "../inc/free.h"

/*

	C ->	Interrumpe la linea actual. limpia la entrada y 
			nuevo prompt y devuelve 130
	D ->	Si se presiona en una linea vacia termina shell, si esta en 
			un comando, teermmina el comando
	\ ->	Cuando es interactivo no hace nada, en programas como cat 
			o vim termina el proceso: 131

*/

int	g_exit_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("QUITING\n");
	}
}

static void	read_prompt(t_data *data)
{
	char	*line;

	while (!data->end)
	{
		line = readline("minishell> ");
		if (!line)
			return ;
		if (!ft_isempty(line))
		{
			if (is_closed(line))
				line = process_command(line, data);
		}
		if (line[0])
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
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	read_prompt(&data);
	ft_free_data(&data);
	return (g_exit_status);
}
