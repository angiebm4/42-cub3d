/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:52:47 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:52:52 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	frame_increment(t_cube *cube)
{
	cube->frame_duration = (cube->frame_duration + 1) % FRAME_DURATION;
	if (cube->frame_duration == 0)
		cube->frame = (cube->frame + 1) % FRAMES;
}

int	render(t_cube *cube)
{
	frame_increment(cube);
	raycasting(cube);
	compass(cube);
	mini_map(cube);
	return (0);
}
