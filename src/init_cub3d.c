
#include "../cub3d.h"
#include <stddef.h>

static	size_t	get_plane_distance(void)
{
	return (((double) WINDOW_WIDTH / 2) / tan(deg_to_rad((double) FOV / 2)));
	// TODO: maybe acutally round this number to sth else for performance reasons
}

static t_deg	get_dir_angle(t_fields init_dir)
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

static void	set_view(t_view *view, t_fields init_dir)
{
	view->plane_distance = get_plane_distance();
	view->dir_angle = get_dir_angle(init_dir);
}

t_error	init_cub3d(t_cub3d *cub3d, t_input *input)
{
	set_view(&cub3d->view, PLAYER_EAST);
	return (0);
}
