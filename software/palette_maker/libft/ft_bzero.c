/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 13:37:23 by vordynsk          #+#    #+#             */
/*   Updated: 2020/03/07 15:31:14 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;
	size_t			i;

	if (s == NULL)
	{
		return ;
	}
	i = 0;
	buf = (unsigned char *)s;
	while (i < n)
	{
		buf[i++] = 0;
	}
}
