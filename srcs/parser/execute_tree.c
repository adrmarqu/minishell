/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:52:56 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/08/03 14:23:25 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include "../../inc/free.h"
#include <sys/wait.h>

static int	execute_operator(t_cmd *cmd, t_data *data)
{
	int	status;

	status = execute_cmd_tree(cmd->left, data, -1, -1);
	if ((cmd->op == OR && status != 0) || (cmd->op == AND && status == 0))
		status = execute_cmd_tree(cmd->right, data, -1, -1);
	return (status);
}

static void	delete_node_redir(t_token **token)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	curr = *token;
	prev = NULL;
	while (curr && curr->next)
	{
		if (get_redir_type(curr->value) != EMPTY)
		{
			next = curr->next->next;
			curr->next->next = NULL;
			ft_free_token(curr);
			if (prev)
				prev->next = next;
			else
				*token = next;
			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int execute_pipe(t_cmd *cmd, t_data *data, int input, int output)
{
    int i;
    int pipefd[2];
    int prev_fd = input;
    pid_t *pids;

    pids = malloc(sizeof(pid_t) * cmd->n_pipes);
    if (!pids)
        return (perror("malloc"), 1);

    for (i = 0; i < cmd->n_pipes; i++)
    {
        // Excepto el último comando, creamos un pipe
        if (i < cmd->n_pipes - 1)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                free(pids);
                return 1;
            }
        }
        else
        {
            // Último comando usa output (o stdout si output == -1)
            pipefd[0] = -1;
            pipefd[1] = output;
        }

        pids[i] = fork();
        if (pids[i] < 0)
        {
            perror("fork");
            free(pids);
            return 1;
        }

        if (pids[i] == 0)
        {
            // Proceso hijo

            // Redirige la entrada estándar (prev_fd) si no es -1
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Si no es el último comando, redirige la salida al pipe de escritura
            if (i < cmd->n_pipes - 1)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            else if (output != -1)
            {
                dup2(output, STDOUT_FILENO);
            }

            // Ejecutar el comando actual (cmd->pipes[i]) llamando a execute_cmd_tree
            // input y output aquí no se usan porque ya hicimos dup2
            int ret = execute_cmd_tree(&(t_cmd){cmd->pipes[i], NULL, cmd->n_pipes, VOID, NULL, NULL}, data, -1, -1);
            exit(ret);
        }

        // Proceso padre

        // Cierra el extremo de escritura anterior si existía
        if (prev_fd != -1)
            close(prev_fd);

        // Cierra el extremo de escritura del pipe actual para preparar la siguiente iteración
        if (i < cmd->n_pipes - 1)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];  // El siguiente hijo leerá de este pipe
        }
    }

    // Esperar a todos los hijos
    int status = 0;
    for (i = 0; i < cmd->n_pipes; i++)
    {
        int wstatus;
        waitpid(pids[i], &wstatus, 0);
        if (i == cmd->n_pipes - 1 && WIFEXITED(wstatus))
            status = WEXITSTATUS(wstatus);
    }

    free(pids);
    return status;
}


int	execute_cmd_tree(t_cmd *cmd, t_data *data, int input, int output)
{
	if (!cmd)
		return (fd_printf(2, "ERROR CMD\n"), 1);
	if (cmd->op == PIPE)
		return (execute_pipe(cmd, data, input, output));
	else if (cmd->op == OR || cmd->op == AND)
		return (execute_operator(cmd, data));
	if (!expand(&cmd->command, data))
		return (1);
	if (heredoc(cmd->command))
		return (1);
	if (set_redirections(cmd->command, &input, &output))
		return (1);
	delete_node_redir(&cmd->command);
	if (!cmd->command)
		return (0);
	return (execute(cmd, data, input, output));
}
