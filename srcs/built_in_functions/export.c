/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:01:27 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 18:57:51 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	env_is_valid(char *target)
{
	int	i;

	i = 1;
	if (target[0] != '_' && !ft_isalpha(target[0]))
		return (0);
	while (target[i])
	{
		if (ft_isalpha(target[i]) || ft_isdigit(target[i]) || target[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	split_key_value(char *line, char **new_key, char **new_value)
{
	int	len;

	len = 0;
	while (line[len] != '=' && line[len] != '\0')
		len++;
	*new_key = (char *)malloc(sizeof(char) * len + 1);
	if (!*new_key)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(*new_key, line, len + 1);
	if (line[len] == '\0')
		*new_value = NULL;
	else
	{
		*new_value = (char *)malloc(sizeof(char) * (ft_strlen(line) - len));
		if (!*new_value)
			perror_and_exit("cannot allocate memory\n", ENOMEM);
		ft_strlcpy(*new_value, line + len + 1, ft_strlen(line) - len);
	}
}

static void	invalid_env(char *new_key, char *new_value)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(new_key, STDERR_FILENO);
	if (new_value)
	{
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putstr_fd(new_value, STDERR_FILENO);
		free(new_value);
	}
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	free (new_key);
}

void	add_new_env(t_env *env, t_list *arg)
{
	t_list	*temp;
	char	*line;
	char	*new_key;
	char	*new_value;

	temp = arg;
	while (temp != NULL)
	{
		new_key = NULL;
		new_value = NULL;
		line = (char *)temp->content;
		split_key_value(line, &new_key, &new_value);
		if (env_is_valid(new_key))
			modify_env_node(env, new_key, new_value);
		else
			invalid_env(new_key, new_value);
		temp = temp->next;
	}
}

int	execute_export(t_info *info, t_process *process)
{
	if (process->option)
	{
		return (error_option("export", info, process));
	}
	else if (!process->arg)
	{
		print_export(info->env);
	}
	else
	{
		add_new_env(info->env, process->arg);
	}
	return (exit_process(info, process, 0));
}
