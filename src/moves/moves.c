/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:22 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:58:25 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	change_position(int keycode, t_cube *cube)
{
	if (keycode == W || keycode == UP)
		move_player(1, cube);
	if (keycode == S || keycode == DOWN)
		move_player(-1, cube);
}

static void	change_vision(int keycode, t_cube *cube)
{
	if (keycode == A || keycode == LEFT)
		rotate_player(-ROTATION_SPEED, &cube->pj);
	if (keycode == D || keycode == RIGHT)
		rotate_player(ROTATION_SPEED, &cube->pj);
}

void	moves(int keycode, t_cube *cube)
{
	if (keycode == W || keycode == UP || keycode == S || keycode == DOWN)
		change_position(keycode, cube);
	if (keycode == A || keycode == LEFT || keycode == D || keycode == RIGHT)
		change_vision(keycode, cube);
}
