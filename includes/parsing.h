/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:46:19 by dim               #+#    #+#             */
/*   Updated: 2022/04/02 03:48:49 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"
#define NO_Q 0
#define SINGLE_Q 1
#define DOUBLE_Q 2

int		check_quote(const char *chr, int *status);


#endif