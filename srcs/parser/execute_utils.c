/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:57:48 by adrmarqu          #+#    #+#             */
/*   Updated: 2025/07/04 17:10:13 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

bool	isbuiltin(char *command)
{
	int			i;
	const int	len = ft_strlen(command);
	const char	*builtins[] = {"cd", "exit", "export", "unset", "echo",
		"pwd", "env", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], command, len))
			return (true);
		i++;
	}
	return (false);
}
