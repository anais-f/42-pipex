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

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	pid_t	pid;

	printf("je fork ici\n");
	pid = fork();
	if (pid == -1)
		return (-1);
//	printf("fork reussi\n");
//	if (pid == 0)
//		printf("Fils = je suis le fils, mon pid est %d\n", pid);
//	else if (pid > 0)
//		printf("Pere = je suis le pere, le pid de mon fils est %d\n", pid);

	if (pid == 0)
	{
		printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
		sleep(1); // Attendre 1 seconde.
		printf("Fils : Termine !\n");
	}
	else if (pid > 0)
	{
		printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
		printf("Pere : Termine !\n");
	}

	return (0);
}

