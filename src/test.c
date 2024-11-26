
#include "../cub3d.h"
#include <sys/types.h>
#include <unistd.h>

void	put_scaled_vertical(mlx_image_t *dst_img, mlx_image_t *src_img, size_t new_height, size_t x, size_t y)
{
	double	scale_factor;
	size_t	i;

	scale_factor = (double) new_height / src_img->height;

	i = 0;
	while (i < new_height)
	{
		mlx_put_pixel(dst_img, x, y, get_pxl_rgba(src_img, y / scale_factor, x));
		i++;
		y++;
	}
}

typedef struct s_imgs
{
	mlx_image_t *src_img;
	mlx_image_t *cur_screen;
	// mlx_image_t *nxt_screen;
} t_imgs;

void	my_loop_hook2(void *arg)
{
	// t_imgs *imgs = (t_imgs *) arg;
	// static	size_t	new_height = 64;
	//
	// sleep(2);
	// new_height *= 2;
}

// int	main(int argc, char *argv[])
// {
// 	mlx_t *mlx;
// 	mlx_texture_t	*txtre;
// 	t_imgs	imgs;
//
// 	mlx = mlx_init(512, 512, "test", true);
// 	if (!mlx)
// 	{
// 		perror("mlx_init");
// 		return (-1);
// 	}
// 	imgs.cur_screen = mlx_new_image(mlx, 512, 512);
// 	if (!imgs.cur_screen)
// 	{
// 		perror("mlx_new_image");
// 		return (-1);
// 	}
// 	txtre = mlx_load_png("./textures/bricksx64.png");
// 	if (!txtre)
// 	{
// 		perror("mlx_load_png");
// 		return (-1);
// 	}
// 	imgs.src_img = mlx_texture_to_image(mlx, txtre);
// 	if (!imgs.src_img)
// 	{
// 		mlx_delete_texture(txtre);
// 		perror("mlx_texture_to_image");
// 		return (-1);
// 	}
// 	mlx_delete_texture(txtre);
//
//
//
// 	mlx_image_to_window(mlx, imgs.src_img, 0, 256);
// 	for (int i = 0; i < 64; ++i )
// 	{
// 		put_scaled_vertical(imgs.cur_screen, imgs.src_img, 64, i, 0);
// 	}
// 	mlx_image_to_window(mlx, imgs.cur_screen, 0, 0);
// 	mlx_loop_hook(mlx, my_loop_hook2, &imgs);
// 	mlx_set_setting(MLX_STRETCH_IMAGE, true);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
//
// }
