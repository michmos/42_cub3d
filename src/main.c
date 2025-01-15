/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/12 16:39:16 by dode-boe      #+#    #+#                 */
/*   Updated: 2025/01/15 20:36:54 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


//add player_img on minimap to parms here, and move it in the move function.
// Can't do it in draw_view, bc there is no comparison point there to see what moved
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
		draw_view(cub);
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
	if (draw_minimap(&cub3d) == -1)
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
