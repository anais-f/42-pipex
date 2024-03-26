/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/26 16:14:42 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc <= 5)
	{
		ft_printf("Error : invalid parameters\n");
		return (-1);
	}
	init_and_open_var(&data, argc, argv);
	while (data.i < argc - 1)
	{
		if (pipe(data.pipe_fd) == -1)
		{
			perror("Pipe");
			exit (1);
		}
		find_path_cmd(&data, argv, envp);
		fork_and_exec(&data, argv, argc, envp);
	}
	close_parent(&data);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

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

void	close_parent(t_data *data)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close(data->temp_fd_in);
}
