/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:05:23 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 14:10:15 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	mouse_init(t_cube *cube)
{
	ft_bzero(&cube->graphic->mouse, sizeof(t_mouse));
	cube->graphic->mouse.last_x = -1;
	cube->graphic->mouse.mouse_vision = 1;
	cube->graphic->mouse.fixed = 0;
}
