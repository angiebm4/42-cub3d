/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:00:30 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 14:00:35 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	reset_pixel(t_pixel *pixel)
{
	pixel->red = PIXEL_DEFAULT;
	pixel->green = PIXEL_DEFAULT;
	pixel->blue = PIXEL_DEFAULT;
}

int	pixel_is_valid(t_pixel *pixel)
{
	return (
		pixel->red >= PIXEL_MIN && pixel->red <= PIXEL_MAX && \
		pixel->green >= PIXEL_MIN && pixel->green <= PIXEL_MAX && \
		pixel->blue >= PIXEL_MIN && pixel->blue <= PIXEL_MAX
	);
}

int	pixel_is_default(t_pixel *pixel)
{
	return (
		pixel->red == PIXEL_DEFAULT && \
		pixel->green == PIXEL_DEFAULT && \
		pixel->blue == PIXEL_DEFAULT
	);
}

void	pixel_copy(t_pixel *dest, t_pixel *src)
{
	if (!dest || !src)
		return ;
	dest->red = src->red;
	dest->green = src->green;
	dest->blue = src->blue;
}

int	pixel_conversor(t_pixel *pixel)
{
	unsigned char	rgb[3];

	rgb[0] = pixel->red;
	rgb[1] = pixel->green;
	rgb[2] = pixel->blue;
	return ((rgb[0] << 16) + (rgb[1] << 8) + rgb[2]);
}
