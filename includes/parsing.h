/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:46:19 by dim               #+#    #+#             */
/*   Updated: 2022/04/03 20:10:04 by dim              ###   ########.fr       */
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


int		check_quote(const char *chr, int *status);


#endif