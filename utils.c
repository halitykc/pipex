
#include "pipex.h"

void	free_split(char **split)
{
	int i = 0;

	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


void    init_pipes(int pipes[][2], int argc)
{
    int i;

    i = -1;
    while (++i < argc - 4)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("Pipe Failed\n");
            exit(EXIT_FAILURE);
        }
    }
}

void    close_fds(int argc, int pipes[][2], int infile, int outfile)
{
    int j;

    j = -1;
    while (++j < argc)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
    close(outfile);
    close(infile);
}

void    wait_for_childs(int argc)
{
    int i;

    i = -1;
    while (++i < argc)
    {
        wait(NULL);
    }
    
}

void run_command(char *arguments)
{
    char *cmd;
    char **args;
    char *temp;

    args = ft_split(arguments, ' ');
    cmd= "/usr/bin/";
    temp = args[0];
    args[0] = ft_strjoin(cmd, args[0]);
    free(temp);
    execve(args[0], args,NULL);
    exit(EXIT_FAILURE);
}

void    start_fork(int pipes[][2], int argc, char **argv, t_pipex pipex_info)
{
    int i;

    i = -1;
    while (++i < argc - 3)
    {
        if (fork() == 0)
        {
            if (i == 0)
                dup2(pipex_info.infile, STDIN_FILENO);
            else
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i == argc - 4)
                dup2(pipex_info.outfile, STDOUT_FILENO);
            else
                dup2(pipes[i][1], STDOUT_FILENO);
            close_fds(argc - 4, pipes, pipex_info.infile, pipex_info.outfile);
    		run_command(argv[i + 2]);
        }
    }
    
}

void    start_pipex(t_pipex *pipex, int argc, char **argv)
{
    pipex->infile = open(argv[1], O_RDONLY);
    pipex->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC);
}

char    *pars_cmd(char *argv)
{
    char    *res;
    char    **split;
    char    *path;
    
    path = "/usr/bin/";
    split = ft_split(argv, ' ');
    res = ft_strjoin(path, split[0]);
	free_split(split);
    return (res); 
}

void    check_if_validfile(char *file)
{
    if (access(file, F_OK) != 0)
    {
        write(1, "==> File Doesnt Exist!\n", 24);
        exit(EXIT_FAILURE);
    }
    if (access(file, R_OK | W_OK) != 0)
    {
        write(1, "==> Check File Permisions!\n", 28);
        exit(EXIT_FAILURE);
    }
    
}

void    check_if_validcmd(char *argv)
{
    char *cmd;

    cmd = pars_cmd(argv);
    printf("%s\n", cmd);
    if (access(cmd, X_OK) != 0)
    {
        write(1, "==> Check Command!\n", 20);
        free(cmd);
        exit(EXIT_FAILURE);
    }
    free(cmd);
}

void    control_params(int argc, char **argv)
{
    int i;

    i = 0;
    while (++i < argc)
    {
        if(i == 1 || i == argc - 1)
            check_if_validfile(argv[i]);
        else
            check_if_validcmd(argv[i]);
    }
}