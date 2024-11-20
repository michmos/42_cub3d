
#include "../cub3d.h"
#include <stddef.h>

static	size_t	get_plane_distance(size_t window_width)
{
	return (((double) window_width / 2) / tan(deg_to_rad((double) FOV / 2)));
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

static void	set_view(t_view *view, t_fields init_dir, size_t window_width)
{
	view->plane_distance = get_plane_distance(window_width);
	view->dir_angle = get_dir_angle(init_dir);
}

static t_error	set_window(t_window *window, size_t map_width, size_t map_height)
{
	window->width = map_width * BLOCK_SIZE;
	window->height = map_height * BLOCK_SIZE;
	// TODO: maybe call this later after all setup done
	window->mlx = mlx_init(window->width, window->height, "cub3d", true);
	if (!window->mlx)
	{
		// TODO: puterror
		return (-1);
	}
	return (0);
}

t_error	init_cub3d(t_cub3d *cub3d, t_input *input)
{
	if (set_window(&cub3d->window, cub3d->map.width, cub3d->map.height))
	{
		return (-1);
	}
	set_view(&cub3d->view, PLAYER_EAST, cub3d->window.width);
	return (0);
}
