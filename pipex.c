#include "pipex.h"


void	ft_free(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
}


int main(int argc, char *argv[])
{
	if (argc >= 5)
	{
		int pipes[argc - 4][2];
		t_pipex pipe_infos;
		control_params(argc, argv);
		start_pipex(&pipe_infos, argc, argv);
		init_pipes(pipes, argc);
		start_fork(pipes, argc, argv, pipe_infos);
		close_fds(argc -4, pipes, pipe_infos.infile, pipe_infos.outfile);
		wait_for_childs(argc - 3);
		return 0;
	}
}