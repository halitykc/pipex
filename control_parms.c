/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:57:00 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/31 14:09:21 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	check_if_validfile(char *file)
{
	if (access(file, F_OK) != 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	if (access(file, R_OK | W_OK) != 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
}

void	check_if_validfile2(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK | W_OK) != 0)
		{
			perror(file);
			return ;
		}
	}
}

int	output_file_exist(char *outfile)
{
	if (access(outfile, F_OK) != 0)
	{
		return (1);
	}
	else
		return (0);
}

void	control_params(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '\0')
		{
			write(1,
				"Thats how yu use it ./pipex file1 \"cmd\" \"cmd2\" file2\n",
				54);
			exit(EXIT_FAILURE);
		}
	}
	if (!output_file_exist(argv[argc - 1]))
	{
		check_if_validfile(argv[argc - 1]);
	}
}
