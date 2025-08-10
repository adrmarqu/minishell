/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:57:21 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/10 14:20:47 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../inc/global.h"

void	rl_base_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	rl_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	ex_signal(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	else if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	g_exit_status = 128 + sig;
}

void	pipe_signal(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
	else if (sig == SIGQUIT)
		g_exit_status = 131;
}

void	set_signals(int level, int intmode, int quitmode)
{
	if (intmode == 0)
		signal(SIGINT, SIG_IGN);
	else if (intmode == 1)
		signal(SIGINT, SIG_DFL);
	else if (intmode == 2 && level == 1)
		signal(SIGINT, rl_base_signal);
	else if (intmode == 2 && level > 1)
		signal(SIGINT, rl_signal);
	else if (intmode == 3 && level == 1)
		signal(SIGINT, ex_signal);
	else if (intmode == 3 && level > 1)
		signal(SIGINT, pipe_signal);
	if (quitmode == 0)
		signal(SIGQUIT, SIG_IGN);
	else if (quitmode == 1)
		signal(SIGQUIT, SIG_DFL);
	else if (quitmode == 2)
		signal(SIGQUIT, pipe_signal);
	else if (quitmode == 3 && level == 1)
		signal(SIGQUIT, ex_signal);
	else if (quitmode == 3 && level > 1)
		signal(SIGQUIT, pipe_signal);
}
