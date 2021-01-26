#include "includes/libft.h"

void	ft_get_address(void *addr, void *ptr)
{
	unsigned char	address[8];
	int				i;
	int				j;
	char			*buf;

	if (addr == NULL)
		return ;
	ft_memset(addr, 48, 16);
	ft_memcpy((void *)address, (void *)&ptr, 8);
	i = 7;
	j = 0;
	while (i >= 0)
	{
		buf = ft_itoa_base((int)address[i], 16);
		if (buf == NULL)
			return ;
		ft_memcpy(&addr[j], buf, ft_strlen(buf));
		free(buf);
		i--;
		j += 2;
	}
}
