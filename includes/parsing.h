/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:46:19 by dim               #+#    #+#             */
/*   Updated: 2022/04/06 17:55:23 by dim              ###   ########.fr       */
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

void	perror_in_parsing(char *line);
void	add_char_to_str(char **str, char ch);
int		check_quote(const char *chr, int *status);


void	save_token(t_process *process, const char *token, int tag);
int		check_token(t_porcess *process, char **new_str, char **token, int *tag);
char 	*replace_env_to_value(t_info *info, const char *line, int len);
int		parse_process(t_process *process, t_info *info,
						const char *line, int len);

#endif