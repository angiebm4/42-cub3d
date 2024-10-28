/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:57:49 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:57:53 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	mouse_controller(int keycode, t_cube *cube)
{
	if (keycode == MOUSE_VISIBILITY_KEY)
		mouse_display(cube);
	else if (keycode == MOUSE_FIX_KEY)
		mouse_fix(&cube->graphic->mouse);
}
