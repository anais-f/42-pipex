/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/25 14:07:45 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_data	data;


	if (argc != 5)
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
	//	printf("commande recu main = %s\n", data.str_path);
		
		// if (data.str_path != NULL)
		// {

			data.pid = fork();
			if (data.pid == -1)
			{
				perror("fork");
				exit (1);
			}
			if (data.pid == 0)
				create_child(&data, argv, argc, envp);
			dup2(data.pipe_fd[0], data.temp_fd_in);
			close(data.pipe_fd[0]);
			close(data.pipe_fd[1]);	
		// }

			
		data.i++;
		free_all(data.cmd, data.str_path);
	}
	close(data.infile_fd);
	close(data.outfile_fd);
	close(data.temp_fd_in);
	
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);

}

void	find_path_cmd(t_data *data, char **argv, char **envp)
{
	data->cmd = ft_split(argv[data->i], ' ');
	if (data->cmd == NULL)
	{
		free_all(data->cmd, NULL);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		return ;
	}
	if (data->cmd[0] == 0)
	{
		//free_all(data->cmd, NULL);
		dprintf(2, "Command '' not found\n");
		data->str_path = NULL;
	}
	else if (bool_search_cmd(data->cmd[0], '/') == 0)
	{
		data->str_path = parse_env_and_path(envp, data->cmd);
		// if (data->str_path == NULL)
		// {
		// 	// close(data->pipe_fd[0]);
		// 	// close(data->pipe_fd[1]);
		// 	//free_all(data->cmd, NULL);
		// }
	}
	else
	{
		data->str_path = check_abs_path(data->cmd);
		// if (data->str_path == NULL)
		// {
		// 	// close(data->pipe_fd[0]);
		// 	// close(data->pipe_fd[1]);
		// //	free_all(data->cmd, NULL);
		// }
	}
}
