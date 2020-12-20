#include "includes/libft.h"

void	ft_print_bytes(void *data, size_t len)
{
	size_t			i;
	char			*buf;
	unsigned char	*bytes;

	if (data == NULL)
		return ;
	bytes = (unsigned char *)data;
	i = 0;
	while (i < len)
	{
		buf = ft_itoa_base((int)bytes[i], 16);
		if (buf == NULL)
			break ;
		if (ft_strlen(buf) < 2)
			ft_putchar('0');
		ft_putstr(buf);
		free(buf);
		i++;
	}
	ft_putchar('\n');
}
