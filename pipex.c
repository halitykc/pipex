/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:06:06 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 15:46:54 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
}

int	main(int argc, char *argv[], char **envp)
{
	int		pipe[2];
	t_pipex	pipe_infos;

	if (argc == 5)
	{
		control_params(argc, argv);
		start_pipex(&pipe_infos, argc, argv, envp);
		init_pipes(pipe);
		start_fork(pipe, argc, argv, pipe_infos);
		close_fds(pipe, pipe_infos.infile, pipe_infos.outfile);
		wait_for_childs();
		return (0);
	}
}


// int	main(int argc, char *argv[], char **envp)
// {
// 	t_pipex	pipe_infos;
// 	(void)argc;
// 	(void)argv;
// 	pipe_infos.paths = path_find(envp); // free_split ile tam temizleniyor
// 	pipe_infos.cmd = pars_cmd(argv[1], pipe_infos);
// 	run_command(argv[1], pipe_infos);




// 	return (0);
// }
