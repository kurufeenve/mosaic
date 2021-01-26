/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bytes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:03:55 by vordynsk          #+#    #+#             */
/*   Updated: 2020/03/07 15:47:24 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*static void				ft_print_address(void *ptr)
{
	unsigned char	address[8];
	int				i;
	char			*buf;

	ft_memcpy((void *)address, (void *)&ptr, 8);
	i = 7;
	while (i >= 0)
	{
		buf = ft_itoa_base((int)address[i], 16);
		if (buf == NULL)
			return ;
		if (ft_strlen(buf) == 1)
			ft_putchar('0');
		ft_putstr(buf);
		free(buf);
		i--;
	}
}*/
#include <stdio.h>
void					ft_xxd(void *data, size_t len)
{
	size_t			i;
	size_t			line_i;
	char			*line;
	char			*buf;
	unsigned char	*bytes;

	if (data == NULL)
		return ;
	bytes = (unsigned char *)data;
	line = ft_strnew(80);
	//ft_memset(line, '0', 60);
	ft_bzero(line, 80);
	i = 0;
	line_i = 16;
	while (i < len)
	{
		ft_get_address(line, &data[i]);
		ft_memcpy((void *)&line[line_i], ": ", 2);
		ft_memcpy((void *)&line[60], bytes, (16 > len ? len : 16));
		line_i += 2;
		while (line_i < 60 && i < len)
		{
			buf = ft_itoa_base((int)bytes[i], 16);
			if (buf == NULL)
				break ;
			ft_memcpy((void *)&line[line_i], buf, ft_strlen(buf));
			if (i % 2)
			{
				line_i += 2;
				i++;
				line[line_i++] = ' ';
				continue ;
			}
			line_i += 2;
			i++;
		}
		ft_memset((void *)&line[line_i], ' ', (60 - line_i));
		ft_putendl(line);
		/*if (buf == NULL)
		{
			ft_putstr(line);
			break ;
		}
		if (!(i % 16))
		{
			ft_get_address(line, );
		}
		if (ft_strlen(buf) == 1)
			ft_putstr(": 0");
		else
			ft_putstr(": ");
		ft_putstr(buf);
		ft_putchar('\n');
		free(buf);*/
		bytes++;
		i++;
	}
	ft_putchar('\n');
	free(line);
}

/*int		main(void)
{
	char	a[] = "abcdef   fsdfgsdgsdgsfdgssdgsdfgsdfgsdfgsdfgs";

	ft_xxd((void *)a, ft_strlen(a));
	return (0);
}*/
