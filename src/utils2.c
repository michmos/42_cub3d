/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 11:23:50 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/22 11:18:47 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

// divide by block size through bit shifting
u_int32_t	div_by_block_size(u_int32_t num)
{
	static int	log2_blocks_size = 0;

	if (log2_blocks_size == 0)
		log2_blocks_size = (int)log2(BLOCK_SIZE);
	return (num >> log2_blocks_size);
}

// multiply by block size through bit shifting
u_int32_t	mult_by_block_size(u_int32_t num)
{
	static int	log2_blocks_size = 0;

	if (log2_blocks_size == 0)
		log2_blocks_size = (int)log2(BLOCK_SIZE);
	return (num << log2_blocks_size);
}

// returns the rgb value
u_int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// returns the rgb value of pixel x, y in img
t_rgb	get_pxl_rgba(mlx_image_t *img, int y, int x)
{
	size_t	pixel_index;
	uint8_t	*pixel_data;

	pixel_index = img->width * y + x;
	pixel_data = &img->pixels[pixel_index * 4];
	return ((t_rgb){.r = pixel_data[0], .g = pixel_data[1], .b = pixel_data[2],
		.a = pixel_data[3]});
}
