
#include "../cub3d.h"

// multiply by block size through bit shifting
u_int32_t mult_by_block_size(u_int32_t num)
{
	return (num << LOG2_BLOCKS_SIZE);
}

// returns the rgb value
u_int32_t get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// returns the rgb value of pixel x, y in img
t_rgb get_pxl_rgba(mlx_image_t *img, int y, int x)
{
	size_t pixel_index;
	uint8_t *pixel_data;

	pixel_index = img->width * y + x;
	// multiply by 4 to account for r, g, b, a
	pixel_data = &img->pixels[pixel_index * 4];
	return ((t_rgb){.r = pixel_data[3], .g = pixel_data[2], .b = pixel_data[1], .a = pixel_data[0]});
}
