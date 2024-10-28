/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:53:46 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:54:47 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->size_line * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->data_addr)) = color;
}
