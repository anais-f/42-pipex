/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/16 10:43:52 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
    int pipefd[2];
	t_data	data;
	char **cmd;
	char *str;
	int i = 0;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit (1);
	}

	data.infile_fd = open(argv[1], O_RDONLY);
	data.outfile_fd = open (argv[argc - 1], O_RDWR /*| O_CREAT */| O_TRUNC);

	cmd = ft_split(argv[2], ' ');
	str = parse_env(envp, cmd);
	dup2(data.infile_fd, STDIN_FILENO);

	execve(str, cmd, envp);




	return (0);
}

char	*build_cmd_path(char *str)
{
	char	**argv_cmd_array;
	//int i = 0;

	argv_cmd_array = ft_split(str, ' ');
//	while (argv_cmd_array[i])
//	{
//		printf("%s\n", argv_cmd_array[i]);
//		i++;
//	}
	return (argv_cmd_array);

//main
//	int	i = 2;
//	while(argv[i] && i < argc - 1) //
//	{
//		build_cmd_path(argv[i]);
//		i++;
//	}
}

// ajouter les access de commande et checker si elles existent
// split la commande argv avec split sur espace
//  verifier avant de join avec / et la commande si l'argument
