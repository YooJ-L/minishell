/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:23:42 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:35:35 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**create_sentences(char *s, char *sep)
{
	int		idx;
	size_t	flag;
	size_t	count;
	char	**sentences;

	idx = -1;
	flag = 0;
	count = 0;
	while (s[++idx])
	{
		if (ft_strchr(sep, s[idx]))
		{
			s[idx] = '\0';
			if (flag)
				count++;
			flag = 0;
		}
		else
			flag = 1;
	}
	if (flag)
		count++;
	sentences = (char **)malloc(sizeof(char *) * (count + 1));
	sentences[count] = NULL;
	return (sentences);
}

static void	clear_sentences(char **array, size_t count)
{
	size_t	idx;

	idx = 0;
	while (idx < count)
		free(array[idx++]);
	free(array);
}

static int	fill_sentences(char **sentences, char *sentence, size_t length)
{
	size_t	idx;
	size_t	count;

	idx = 0;
	count = 0;
	while (idx < length)
	{
		if (sentence[idx] != '\0')
		{
			sentences[count++] = ft_strdup(sentence + idx);
			if (sentences[count - 1] == NULL)
			{
				clear_sentences(sentences, count);
				return (0);
			}
			while (sentence[idx] != '\0')
				idx++;
		}
		idx++;
	}
	return (1);
}

char	**ft_split_str(char const *s, char *sep)
{
	char	**sentences;
	char	*sentence;
	size_t	length;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	sentence = ft_strdup(s);
	if (sentence == NULL)
		return (NULL);
	sentences = create_sentences(sentence, sep);
	if (sentences == NULL)
		return (NULL);
	if (!fill_sentences(sentences, sentence, length))
	{
		free(sentence);
		return (NULL);
	}
	free(sentence);
	return (sentences);
}
