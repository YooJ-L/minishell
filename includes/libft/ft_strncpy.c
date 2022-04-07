/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:05:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 16:06:02 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strncpy(char *dest, const char *src, size_t n)
{
  char	*ret = dest;

  for(int i=0; i<n; i++)
  {
    if((*dest++ = *src++) == 0){
      while(++i < n){
        *dest++ = 0;
      }
      return ret;
    }
  }
  return ret;
}