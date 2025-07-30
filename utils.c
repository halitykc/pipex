/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:09:21 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 17:59:34 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(int pipes[2])
{
	if (pipe(pipes) == -1)
	{
		perror("Pipe Failed\n");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(int pipes[2], int infile, int outfile)
{
	close(pipes[0]);
	close(pipes[1]);
	close(outfile);
	close(infile);
}

void	wait_for_childs(void)
{
	wait(NULL);
	wait(NULL);
}


void	start_fork(int pipes[2], int argc, char **argv, t_pipex pipex_info)
{
	int	i;

	i = -1;
	while (++i < argc - 3)
	{
		if (fork() == 0)
		{
			if (i == 0)
				dup2(pipex_info.infile, STDIN_FILENO);
			else
				dup2(pipes[0], STDIN_FILENO);
			if (i == argc - 4)
				dup2(pipex_info.outfile, STDOUT_FILENO);
			else
				dup2(pipes[1], STDOUT_FILENO);
			close_fds(pipes, pipex_info.infile, pipex_info.outfile);
			pipex_info.cmd = pars_cmd(argv[i + 2], pipex_info);
			run_command(argv[i + 2], pipex_info);
		}
	}
}

void	start_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDWR, 0644);
	if (!output_file_exist(argv[argc - 1]))
	{
		pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else
		pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	pipex->paths = path_find(envp);
}
