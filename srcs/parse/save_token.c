/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:06:09 by dim               #+#    #+#             */
/*   Updated: 2022/04/08 13:25:20 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	save_redirection(t_process *process, char *token)
{
	t_redirection	*new_rd_node;

	new_rd_node = (t_redirection *)malloc(sizeof(t_redirection));
	if (new_rd_node == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	if (token[0] == '<' && token[1] == '\0')
		new_rd_node->symbol = SINGLE_IN;
	else if (token[0] == '<' && token[1] == '<' && token[2] == '\0')
		new_rd_node->symbol = DOUBLE_IN;
	else if (token[0] == '>' && token[1] == '\0')
		new_rd_node->symbol = SINGLE_OUT;
	else if (token[0] == '>' && token[1] == '>' && token[2] == '\0')
		new_rd_node->symbol = DOUBLE_OUT;
	free(token);
	new_rd_node->filename = NULL;
	new_rd_node->next = NULL;
	redir_lstadd_back(&(process->redirect), new_rd_node);
}

void	save_filename(t_process *process, char *token)
{
	t_redirection	*last_redir;

	last_redir = redir_lstlast(process->redirect);
	last_redir->filename = token;
}

void	save_option(t_process *process, char *token)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	new_node->content = (void *)token;
	new_node->next = NULL;
	ft_lstadd_back(&(process->option), new_node);
}

void	save_argument(t_process *process, char *token)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	new_node->content = (void *)token;
	new_node->next = NULL;
	ft_lstadd_back(&(process->arg), new_node);
}

void	save_token(t_process *process, char *token, int tag)
{
	if (token == NULL)
		return ;
	if (tag == INSTRUCTION)
		process->instruction = token;
	else if (tag == FILENAME)
		save_filename(process, token);
	else if (tag == OPTION)
		save_option(process, token);
	else if (tag == ARG)
		save_argument(process, token);
	else if (tag == REDIRECTION)
		save_redirection(process, token);
}