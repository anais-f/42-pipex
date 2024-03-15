/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:50:40 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/08 12:50:40 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"


int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
    int pipefd[2];
	int i = 0;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit (1);
	}

	while (env[i])
	{

	}





//	pid = fork();
//	if (pid == -1) {
//        return (-1);
//    }
//    printf("fork reussi\n");
//    if (pid == 0) // on est dans l'enfant
//    {
//		printf("Enfant = je suis l'enfant, mon pid est %d\n", pid);
//		close(pipefd[1]);
//		while (read(pipefd[0], &buffer, sizeof(buffer)) > 0)
//		{
//			dprintf(STDOUT_FILENO, "Enfant : lecture du parent = %s\n", buffer);
//		}
//		close(pipefd[0]);
//		exit (0);
//    }
//	else if (pid > 0) // on est dans le parent
//    {
//		printf("Parent = je suis le parent, le pid de mon enfant est %d\n", pid);
//		close(pipefd[0]);
//		dprintf(pipefd[1], "Test ecriture chez le parent");
//		close(pipefd[1]);
//		//wait(NULL);
//		exit (0);
//	}


	return (0);
}


//void    parse_env(const char **path_array)
//{
//
//}
