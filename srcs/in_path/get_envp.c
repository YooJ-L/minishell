/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:51 by dim               #+#    #+#             */
/*   Updated: 2022/03/26 20:43:16 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int		get_envp_size(t_env *env)
{
	int	i;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	merge_envp(t_env *env, char **dest_env)
{
	int i;
	int	keylen;
	int	valuelen;

	i = 0;
	keylen = 0;
	valuelen = 0;
	while (env)
	{
		keylen = ft_strlen(env->key);
		valuelen = ft_strlen(env->value);
		dest_env[i] = (char *)malloc(sizeof(char) * (keylen + valuelen + 2));
		if (dest_env[i] == NULL)
			perror_and_exit("cannot allocate memory\n", ENOMEM);
		ft_strlcpy(&dest_env[i][0], env->value, valuelen + 1);
		dest_env[i][keylen] = '=';
		ft_strlcpy(&dest_env[i][keylen + 1], env->value, valuelen + 1);
		i++;
		env = env->next;
	}

}

char	**get_env(t_env *env)
{
	char **dest_env;
	int	size;

	size = get_envp_size(env);
	dest_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (dest_env == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(env, sizeof(char *) * (size + 1));
	merge_envp(env, dest_env);
	return (dest_env);
}