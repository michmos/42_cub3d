
#include "../cub3d.h"

void	loophook(void *param)
{
	t_cub3d 	*cub;
	u_int8_t	moved;

	moved = false;
	cub = (t_cub3d *) param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		moved = move(cub, FORWARD);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		moved = move(cub, BACKWARD);

	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		moved += move(cub, LEFT);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		moved += move(cub, RIGHT);

	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		moved += rotate(cub, COUNTER_CLOCKWISE);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		moved += rotate(cub, CLOCKWISE);

	if (moved)
		draw_view(cub); //redraw 
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
	if (check_settings() == -1)
	{
		return (-1);
	}
	ft_bzero(&input, sizeof(t_input));
	if (parse_file(&input, argv[1]) == -1)
	{
		return (-1);
	}
	if (init_cub3d(&cub3d, &input) == -1)
	{
		free_input(&input);
		return (-1);
	}
	if (draw_minimap(&cub3d) != 0)
	{
		free_input(&input);
		return (-1);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop_hook(cub3d.mlx, loophook, &cub3d);
	draw_view(&cub3d);
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	free_input(&input);
	return (0);
}
