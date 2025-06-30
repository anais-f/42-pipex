/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:11:57 by anfichet          #+#    #+#             */
/*   Updated: 2024/03/26 16:06:21 by anfichet         ###   ########lyon.fr   */
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

typedef struct s_data
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	int		temp_fd_in;
	int		i;
	pid_t	pid;
	char	**cmd;
	char	*str_path;

}	t_data;

void	fork_and_exec(t_data *data, int argc, char **envp);
char	*parse_env_and_path(char **envp, char **cmd);
char	*check_join_path(char **array, t_data *data, char **envp);
char	*check_abs_path(char **cmd);
void	find_path_cmd(t_data *data, char **argv, char **envp);
char	*parse_array_to_path(char **path_array, char **cmd);
int		bool_search_cmd(char *str, int c);
void	free_all(char **array, char *ptr);
char	*ft_join_cmd(char *s1, char *s2);
void	init_and_open_var(t_data *data, int argc, char **argv);
void	ft_close_child(t_data *data);
int		last_child(t_data *data, char *str, char **envp, char **cmd);
int		first_child(t_data *data, char *str, char **envp, char **cmd);
int		create_child(t_data *data, int argc, char **envp);
void	error_with_file(t_data *data, char *str, char **cmd);
void	close_parent(t_data *data);
void	close_str_null(char *str, char **cmd);

#endif