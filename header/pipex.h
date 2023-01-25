/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:21:51 by gclement          #+#    #+#             */
/*   Updated: 2023/01/25 11:25:30 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"

char	**set_argxec(char **cmd, char *filename);
char	**set_argxec_child(char **cmd);
void	call_cmd(char **argxec, char **cmd, char **all_path);
char	**create_array_path(char *envp[]);
void	child(int fd[2], char **argv, char **all_path);

void	*free_2d_array(char **ptr);

#endif
