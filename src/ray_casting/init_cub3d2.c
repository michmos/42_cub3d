/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:41:11 by mmoser            #+#    #+#             */
/*   Updated: 2025/01/15 17:41:46 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	get_plane_distance(void)
{
	return (( WINDOW_WIDTH / 2.0) / tan(deg_to_rad( FOV / 2.0)));
}

t_deg	get_dir_angle(t_fields init_dir)
{
	if (init_dir == PLAYER_EAST)
	{
		return (0);
	}
	else if (init_dir == PLAYER_SOUTH)
	{
		return (270);
	}
	else if (init_dir == PLAYER_WEST)
	{
		return (180);
	}
	else if (init_dir == PLAYER_NORTH)
	{
		return (90);
	}
	else
	{
		assert(!"bad input");
	}
}

void	set_view(t_view *view, t_fields init_dir)
{
	view->plane_distance = get_plane_distance();
	view->dir_angle = get_dir_angle(init_dir);
}
