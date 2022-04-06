/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:26:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 21:34:57 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

static void	print_error(char *to_dir)
{
	char	*error_message;

	error_message = strerror(errno);
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(to_dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

//pwd가 env에 없으면 아무 동작 안함. 새로 만들지도 x
void		update_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	t_env	*temp;
	char	*old_pwd;
	char	*new_pwd;

	getcwd(buf, PATH_MAX); //작업중인 dir의 이름을 buf에 저장.
	new_pwd = ft_strdup(buf);
	temp = env_node_exists("PWD", env);
	if (temp)
	{
		old_pwd = temp->value;
		temp->value = new_pwd;
	}
	temp = env_node_exists("OLDPWD", env);
	if (temp)
	{
		free(temp->value);
		temp->value = old_pwd;
	}
	else
	{
		
	}
}

int			excute_cd(t_info *info, t_process *process)
{
	int		ret;
	char	*to_dir;

	if (process->option)
		return (error_option("cd", info, process));
	if (process->arg)
		to_dir = (char *)(process->arg->content);
	else
		to_dir = get_env_value(info->env, "HOME");
	ret = chdir(to_dir);
	if (ret == -1)
	{
		print_error(to_dir);
		ret = 1;
	}
	update_pwd(info->env);
	return (exit_process(info, process, errno));
}