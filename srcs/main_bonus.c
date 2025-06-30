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

static void	process_commands(t_data *data, char **argv, int argc, char **envp);
static int	setup_data(t_data *data, int argc, char **argv);
static int	check_arguments(int argc, char **argv);


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (check_arguments(argc, argv) == -1)
		return (-1);
	if (setup_data(&data, argc, argv) == -1)
		return (-1);
	process_commands(&data, argv, argc, envp);
	close_parent(&data);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

static int	check_arguments(int argc, char **argv)
{
	if (argc <= 5)
	{
		ft_printf("Error : invalid parameters\n");
		return (-1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)
	{
		ft_printf("Error : invalid parameters for here_doc\n");
		return (-1);
	}
	return (0);
}

static int	setup_data(t_data *data, int argc, char **argv)
{
	data->here_doc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data->here_doc = 1;
		init_and_open_var_here_doc(data, argc, argv);
		if (handle_here_doc(data, argv[2]) == -1)
		{
			ft_printf("Error : here_doc failed\n");
			return (-1);
		}
	}
	else
		init_and_open_var(data, argc, argv);
	return (0);
}

static void	process_commands(t_data *data, char **argv, int argc, char **envp)
{
	while (data->i < argc - 1)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			perror("Pipe");
			exit(1);
		}
		find_path_cmd(data, argv, envp);
		fork_and_exec(data, argc, envp);
	}
}
