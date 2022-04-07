/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:27:30 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 21:52:56 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"
/*
1. arg o, option x
2. option 여러개도 가능 ex) unset a b c
3. Unsetting a variable or function that was not previously set
       shall not be considered an error and does not cause the shell to
       abort.
4. unset 숫자 x ex) unset 12a(x)
5. unset 문자+숫자 o ex) unset a999, unset abcd123
6. unset @ 들어가면 X 앞뒤에 뭐가 오든 안됨.
7. unset 1a(잘못된 인자) a(되는 것) b(되는 것) => a b 지워지고 bash: unset: `1a': not a valid identifier 나옴. 
	안되는 것 여러개 일 때 => 다 출력 	bash: unset: `1a': not a valid identifier
								bash: unset: `2c': not a valid identifier
8. unset (...) => bash: syntax error near unexpected token `...'
9. echo "없는 것" => exit status=0(정상 작동 취급)
	echo "인자가 잘못 된 것 (1a, 11 같은거)" => exit status=1
	echo "잘못된 인자" "없는 것" => exit status=1 (인자 순서 바꿔도 1) (7번 에러문구는 출력됨)
	==> 잘못된 인자가 있으면 에러코드는 1! 다른 건 0!
*/

// int	delete_head_content(t_env **env, char *key)
// {
// 	t_env	**head;

// 	head = env;
// 	if (ft_strncmp((*head)->key, key, ft_strlen(key) + 1) == 0)
// 	{
// 		env = &((*env)->next);
// 		free((*head)->key);
// 		free((*head)->value);
// 		free(*head);
// 		return (1);
// 	}
// 	return (0);
// }

// void	delete_content(t_env **env, char *key)
// {
// 	t_env	*this_node;
// 	t_env	*previous_node;

// 	if (delete_head_content(env, key))
// 		return ;
// 	this_node = *env;
// 	while (this_node->next)
// 	{
// 		if (ft_strncmp(this_node->key, key, ft_strlen(key) + 1) == 0)
// 		{
// 			free(this_node->key);
// 			free(this_node->value);
// 			previous_node->next = this_node->next;
// 			this_node->next = NULL;
// 			free(this_node);
// 			return ;
// 		}
// 		previous_node = this_node;
// 		this_node = this_node->next;
// 	}
// }

// bool	validate_unset_arg(char *content) //잘못된 인자인지 체크
// {
// 	if (ft_isalnum(content[0])) //첫 글자가 숫자이면 error
// 		return (false);
// 	return (true);
// }

// int	execute_unset(t_info *info, t_process *process)
// {
// 	bool	wrong_arg;
// 	t_list	*

// 	wrong_arg = 0;
// 	if (!info->env)
// 		return (exit_process(info, process, 0));
// 	if (process->option)
// 	{
// 		return (error_option("unset", info, process));
// 	}
// 	while (process->arg->next) //인자 여러개여도 가능하니까 arg리스트 반복문 돌림.
// 	{
// 		if (!validate_unset_arg(process->arg->content)) //잘못된 인자 들어왔는지 체크
// 		{
// 			wrong_arg = 1;
// 			printf("bash: unset: `%s': not a valid identifier", process->arg->content);
// 			process->arg = process->arg->next;
// 			continue ;
// 		}
// 		delete_content(&info->env, process->arg->content);
// 		process->arg = process->arg->next;
// 	}
// 	if (wrong_arg)
// 	{
// 		exit_process(info, process, 1);
// 	}
// 	return (exit_process(info, process, 0));
// }

void	delete_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*target;
	int		len;

	tmp = *env;
	len = ft_strlen(str);
	if (!ft_strncmp(tmp->key, str, len + 1))
	{
		tmp = tmp->next;
		free(*env);
		*env = tmp;
		return ;
	}
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(tmp->next->key, str, len + 1))
		{
			target = tmp->next;
			tmp->next = target->next;
			free(target);
			return ;
		}
		tmp = tmp->next;
	}
}

int	execute_unset(t_info *info, t_process *process)
{
	t_list	*arg;
	char	*target;

	if (!info->env)
		return (exit_process(info, process, 0));
	if (process->option)
		return (error_option("unset", info, process));
	arg = process->arg;
	while (arg != NULL)
	{
		target = (char *)arg->content;
		if (env_is_valid(target))
			delete_env(&info->env, target);
		else
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(target, STDERR_FILENO);
			ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
		}
		arg = arg->next;
	}
	return (exit_process(info, process, 0));
}