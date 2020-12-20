/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:01:57 by vordynsk          #+#    #+#             */
/*   Updated: 2020/03/07 15:41:37 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*buf;

	if (b == NULL)
	{
		return (b);
	}
	i = 0;
	buf = b;
	while (i < len)
		buf[i++] = (unsigned char)c;
	return (b);
}
