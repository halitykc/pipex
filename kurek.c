/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kurek.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:06:49 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 15:32:01 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <string.h>

char	*path(char **envp)
{
	while (*envp)
	{
		if (!strncmp(*envp, "PATH", 4))
		{
			*envp = strchr(*envp, '=');
			(*envp)++;
			return (*envp);
		}
		envp++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*s;
	char	**sa;

	(void)argc;
	(void)argv;
	printf("aaaa\nbbbbbbbbbbbb\nvvvvvvvvvvvvvvvvvvv\n");
	return (0);
}
