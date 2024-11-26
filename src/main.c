
#include "../cub3d.h"

void	my_loop_hook(void *arg)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) arg;
	draw_view(cub3d);
	cub3d->view.dir_angle = sum_angle(cub3d->view.dir_angle, 0.5);

// 	get key data
// 	update view.angle and player_pos IF DATA CHANGED
//	redraw image based on new view and pos
}

int	main(int argc, char *argv[])
{
	t_cub3d	cub3d;
	t_input	input;

	if (argc != 2)
	{
		put_err(USAGE_ERR);
		return (-1);
	}
	if (BLOCK_SIZE % 2 != 0)
	{
		put_err(BLOCK_SIZE_ERR);
		return (-1);
	}
	ft_bzero(&input, sizeof(t_input));
	if (parse_file(&input, argv[1]) == -1)
	{
		return (-1);
	}
	if (init_cub3d(&cub3d, &input) == -1)
	{
		return (-1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop_hook(cub3d.mlx, my_loop_hook, &cub3d);
	mlx_loop(cub3d.mlx);

	free_input(&input);
	return (0);
}

