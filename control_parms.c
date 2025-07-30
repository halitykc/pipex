#include "pipex.h"


/*			CONTROL			*/
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
		perror("==> File Doesnt Exist!");
		exit(EXIT_FAILURE);
	}
	if (access(file, R_OK | W_OK) != 0)
	{
		perror("==> Check File Permisions!");
		exit(EXIT_FAILURE);
	}
}

void	check_if_validfile2(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK | W_OK) != 0)
		{
			perror("==> Check File Permisions!");
			return;
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
			write(2,"Wrong Usage! How to use = ./pipex infile cmd1 cmd2 outfile\n", 60);
			exit(EXIT_FAILURE);
		}
	}
	
	i = 0;
	while (++i < argc - 1)
	{	
		if (i == 1)
			check_if_validfile2(argv[i]);
	}
	if (i == argc - 1 && !output_file_exist(argv[argc - 1]))
	{
		check_if_validfile(argv[i]);
	}
}