/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/10 16:02:32 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*output;
	t_env	*env;

	if (parse_env(&env, envp))
		return (-1);
	while (1)
	{
		output = readline("tinyshell$ ");
		if (!output)
		{
			make_error();
		}
		add_history(output);
		free(output);
	}
	return (0);
}
