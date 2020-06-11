#include "includes/libft.h"

void	ft_endian_swap(void *data, int size)
{
	unsigned char	*swap;
	unsigned char	*bytes;
	int				i;

	if (data == NULL || size == 0)
	{
		return ;
	}
	bytes = (unsigned char *)data;
	if ((swap = (unsigned char *)malloc(sizeof(unsigned char) * size)) == NULL)
	{
		return ;
	}
	i = size;
	while (--i > -1)
	{
		swap[i] = *bytes;
		bytes++;
	}
	ft_memcpy(data, (void *)swap, (size_t)size);
	free(swap);
}
