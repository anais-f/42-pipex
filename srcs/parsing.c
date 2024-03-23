/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:24:41 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/23 19:33:39 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parse_env_and_path(char **envp, char **cmd)
{
	char	**path_array;
	char	*join_cmd;
	int		i;

	path_array = NULL;
	join_cmd = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path_array = ft_split(envp[i] + 5, ':');
            if (path_array == NULL)
                return (NULL);
		}
		i++;
	}
	i = 0;
	while (path_array && path_array[i])
	{
		free(join_cmd);
		join_cmd = ft_join_cmd(path_array[i], cmd[0]);
		if (join_cmd == NULL)
			return (NULL);
		if (access(join_cmd, F_OK | X_OK | R_OK) == 0)
		{
			//printf("cmd = %s \n", join_cmd);
			break;
		}
		i++;
	}
	if (path_array && path_array[i] == NULL)
	{
		free(join_cmd);
		dprintf(2, "%s: command parse not found\n", cmd[0]);
		free_all(path_array, NULL);
		join_cmd = NULL;
		//printf("cmd after parse = %s \n", join_cmd);
		return (NULL);
	}
	free_all(path_array, NULL);
	return(join_cmd);
}


char	*check_abs_path(char **cmd)
{
	char	*path_cmd;
//	size_t	i;

	path_cmd = ft_strdup(cmd[0]);
	if (path_cmd == NULL)
		return (NULL);
	// i = ft_protect_strlen(path_cmd);
	// if (path_cmd[i - 1] == '/')
	// {
	// 	dprintf(2, "%s: command not found or exec not executable\n", cmd[0]);
	// 	free_all(NULL, path_cmd);
	// 	return (NULL);
	// }
	if (access(path_cmd, F_OK | X_OK | R_OK) != 0)
	{
		dprintf(2, "%s: command / or exect not found\n", cmd[0]);
		free_all(NULL, path_cmd);
		path_cmd = NULL;
		//return (NULL);
	}
//	printf("str path absolu %s\n", path_cmd);
	return (path_cmd);
}