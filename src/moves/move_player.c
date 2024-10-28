/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:17 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:58:20 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_player(int inc, t_cube *cube)
{
	double		pos_x;
	double		pos_y;
	t_player	*player;

	player = &cube->pj;
	pos_x = player->pos_x + inc * player->dir_x * MOVE_SPEED;
	pos_y = player->pos_y + inc * player->dir_y * MOVE_SPEED;
	if (cube->map[(int)player->pos_y]
		[(int)(pos_x + inc * player->dir_x * SEPARATOR)] == '0')
		player->pos_x = pos_x;
	if (cube->map[(int)(pos_y + inc * player->dir_y * SEPARATOR)]
		[(int)player->pos_x] == '0')
		player->pos_y = pos_y;
}
