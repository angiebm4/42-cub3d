/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:57:37 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:57:40 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	points_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

static void	change_state(int x, int y, t_cube *cube)
{
	if (cube->map[y][x] == 'D')
		cube->map[y][x] = '0';
	else
		cube->map[y][x] = 'D';
}

void	door_interaction(t_cube *cube)
{
	double	x_player;
	double	y_player;
	double	points_diff;
	t_list	*it;
	t_door	*door;

	it = cube->doors;
	x_player = cube->pj.pos_x;
	y_player = cube->pj.pos_y;
	while (it)
	{
		door = it->content;
		points_diff = points_distance(x_player, y_player, door->x + 0.5,
				door->y + 0.5);
		if (points_diff <= INTERACTION_DISTANCE && points_diff > 0.51)
			change_state(door->x, door->y, cube);
		it = it->next;
	}
}
