/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:48:18 by vordynsk          #+#    #+#             */
/*   Updated: 2020/03/02 17:36:18 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memjoin(void *dst, void *src, size_t dst_len, size_t src_len)
{
	unsigned char	*buf;

	if (src == NULL || src_len == 0)
	{
		return dst;
	}
	if (dst == NULL)
	{
		dst = (unsigned char *)malloc(sizeof(unsigned char) * src_len);
		ft_memcpy((void *)dst, (void *)src, src_len);
		return (dst);
	}
	else
	{
		buf = (unsigned char *)malloc(sizeof(unsigned char) * (dst_len + src_len));
		ft_memcpy((void *)buf, dst, dst_len);
		free(dst);
		ft_memcpy((void *)&buf[dst_len], src, src_len);
		return (buf);
	}
}
