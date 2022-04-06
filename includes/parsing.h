/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:46:19 by dim               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/06 17:55:23 by dim              ###   ########.fr       */
=======
/*   Updated: 2022/04/05 21:06:27 by yoojlee          ###   ########.fr       */
>>>>>>> 4ff635e3f6fbaf7d3e153e5d121775a4f5ae5a75
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"
# define NO_Q 0
# define SINGLE_Q 1
# define DOUBLE_Q 2

# define INSTRUCTION 1
# define OPTION 2
# define ARG 3
# define REDIRECTION 4
# define FILENAME 5

# define SINGLE_IN 1
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4


int		check_quote(const char *chr, int *status);
<<<<<<< HEAD

void	perror_in_parsing(char *line);
void	add_char_to_str(char **str, char ch);
int		check_quote(const char *chr, int *status);


void	save_token(t_process *process, const char *token, int tag);
int		check_token(t_porcess *process, char **new_str, char **token, int *tag);
char 	*replace_env_to_value(t_info *info, const char *line, int len);
int		parse_process(t_process *process, t_info *info,
						const char *line, int len);
=======
int		parse_process(t_process *process, t_info *info, const char *line, int len);
char 	*replace_env_to_value(t_info *info, const char *line, int len);
int		check_token(t_porcess *process, char **new_str, char **token, int *tag);
void	save_token(t_process *process, const char *token, int tag);
>>>>>>> 4ff635e3f6fbaf7d3e153e5d121775a4f5ae5a75

#endif