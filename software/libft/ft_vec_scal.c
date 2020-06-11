/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_scal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:34:10 by vordynsk          #+#    #+#             */
/*   Updated: 2018/09/25 14:34:14 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_vec_scal(float *res, t_vector v1, t_vector v2)
{
	*res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
