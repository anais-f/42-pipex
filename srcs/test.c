int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	pid_t	pid;
	//   char *str[] = {argv[1], NULL};
	int pipefd[2];
	char buffer[40];

	printf("argv 0 = %s, argv 1 = %s, argv 2 = %s\n", argv[0], argv[1], argv[2]);
	execve("/usr/bin/ls", &argv[1], NULL);

	if (pipe(pipefd) == -1) {
		return (-1);
	}
	pid = fork();
	if (pid == -1) {
		return (-1);
	}
	printf("fork reussi\n");
	if (pid == 0) // on est dans l'enfant
	{
		printf("Enfant = je suis l'enfant, mon pid est %d\n", pid);
		close(pipefd[1]);
		while (read(pipefd[0], &buffer, sizeof(buffer)) > 0)
		{
			dprintf(STDOUT_FILENO, "Enfant : lecture du parent = %s\n", buffer);
		}
		close(pipefd[0]);
		exit (0);
	}
	else if (pid > 0) // on est dans le parent
	{
		printf("Parent = je suis le parent, le pid de mon enfant est %d\n", pid);
		close(pipefd[0]);
		dprintf(pipefd[1], "Test ecriture chez le parent");
		close(pipefd[1]);
		//wait(NULL);
		exit (0);
	}


	return (0);
}



-----------------------
pid = fork();
//	if (pid == -1)
//		return (-1);
//	printf("fork reussi\n");
//	if (pid == 0)
//		printf("Fils = je suis le fils, mon pid est %d\n", pid);
//	else if (pid > 0)
//		printf("Pere = je suis le pere, le pid de mon fils est %d\n", pid);

-------------------------
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
--------------------------


int	find_outfile(char **argv)
{
	int	i;

	i = 0;
	while(argv[i])
		i++;
	return (i - 1);
}




//char	*build_cmd_path(char *str)
//{
//	char	**argv_cmd_array;
//	//int i = 0;
//
//	argv_cmd_array = ft_split(str, ' ');
////	while (argv_cmd_array[i])
////	{
////		printf("%s\n", argv_cmd_array[i]);
////		i++;
////	}
//	return (argv_cmd_array);
//
////main
////	int	i = 2;
////	while(argv[i] && i < argc - 1) //
////	{
////		build_cmd_path(argv[i]);
////		i++;
////	}
//}