/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:09:06 by vordynsk          #+#    #+#             */
/*   Updated: 2020/03/02 17:09:30 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	size_t		i;
	char		*buf_dest;
	char const	*buf_src;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}
	i = 0;
	buf_dest = dest;
	buf_src = src;
	while (i < n)
	{
		buf_dest[i] = buf_src[i];
		i++;
	}
	return (dest);
}
