
#include "../../cub3d.h"
#include <sys/types.h>

static const  u_int32_t lookup_table[] = {
    256, 253, 250, 248, 245, 243, 240, 238, 235, 233,
    230, 228, 225, 223, 220, 218, 215, 213, 210, 208,
    205, 202, 200, 197, 195, 192, 190, 187, 185, 182,
    179, 177, 174, 172, 169, 167, 164, 162, 159, 156,
    154, 151, 149, 146, 144, 141, 138, 136, 133, 131,
    128, 126, 123, 120, 118, 115, 113, 110, 108, 105,
    102, 100,  97,  95,  92,  90,  87,  84,  82,  79,
     77,  74,  72,  69,  66,  64,  61,  59,  56,  54,
     51,  49,  46,  43,  41,  38,  36,  33,  31,  28
};

u_int16_t	get_shader_multplr(u_int32_t distance)
{
	static const size_t	table_size = sizeof(lookup_table) / sizeof(u_int32_t);
	size_t	idx;

	// div by 8 - determines that the intensity changes
	// every 8 pixels in distance
	idx = distance >> 4;
	if (idx > table_size - 1)
	{
		idx = table_size - 1;
	}
	return (lookup_table[idx]);
}

void	shader_pxl(t_rgb *pxl, u_int32_t shader_mltplr)
{
	// multiply each value by multiplier and divide by 256
	// used to avoid floating point intensities
	pxl->r = (pxl->r * shader_mltplr) >> 8;
	pxl->g = (pxl->g * shader_mltplr) >> 8;
	pxl->b = (pxl->b * shader_mltplr) >> 8;
	pxl->a = (pxl->a * shader_mltplr) >> 8;
}
