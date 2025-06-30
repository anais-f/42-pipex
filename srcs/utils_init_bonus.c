#include "pipex_bonus.h"

void	init_and_open_var(t_data *data, int argc, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd == -1)
		perror (argv[1]);
	data->outfile_fd = 0;
	data->outfile_fd = open (argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
		perror (argv[argc -1]);
	data->temp_fd_in = 0;
	data->i = 2;
	data->pid = 0;
	data->cmd = NULL;
	data->str_path = NULL;
}

void init_and_open_var_here_doc(t_data *data, int argc, char **argv)
{
	data->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->outfile_fd == -1)
		perror(argv[argc - 1]);
	data->temp_fd_in = 0;
	data->i = 3;
	data->pid = 0;
	data->cmd = NULL;
	data->str_path = NULL;
}

void	close_parent(t_data *data)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close(data->temp_fd_in);
	if (data->here_doc)
		unlink(".here_doc_tmp");
}