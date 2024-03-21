/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:11:57 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/12 19:11:57 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_data
{
	int 	infile_fd;
	int 	outfile_fd;
	int 	pipe_fd[2];
	int		temp_fd_in;
	int 	i;
	pid_t	pid;
	char 	**cmd;
	char 	*str_path;

}	t_data;

char	*parse_env_and_path(char **envp, char **cmd);
char	*ft_join_cmd(char *s1, char *s2);
char 	*check_abs_path(char **cmd);
void	free_all(char **array, char *ptr);
int 	first_child(t_data *data, char *str, char **envp, char **cmd);
int 	last_child(t_data *data, char *str, char **envp, char **cmd);
int 	str_bool(char *str, int c);
void	init_var(t_data *data, int argc, char **argv);
int		create_child(t_data *data, char ** argv, int argc, char **envp);
int	pipe_and_path(t_data *data, char **argv, char **envp);

#endif