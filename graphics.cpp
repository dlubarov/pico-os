#include "common.h"

static volatile uint8 *frame_buffer;

static vbe_mode_info_t *vbe_mode_info;

void init_graphics(vbe_mode_info_t *mode_info)
{
  frame_buffer = (uint8 *) mode_info->physbase;
  vbe_mode_info = mode_info;
}

void setpixel(int x, int y, uint8 r, uint8 g, uint8 b)
{
  int w = vbe_mode_info->Xres;
  int r_bits = vbe_mode_info->red_mask_size;
  int g_bits = vbe_mode_info->green_mask_size;
  int b_bits = vbe_mode_info->blue_mask_size;
  int bits_per_pixel = r_bits + g_bits + b_bits;
  int bytes_per_pixel = bits_per_pixel / 8;
  int pixel_offset = (y * w + x) * bytes_per_pixel;
  // TODO: Assumes BGR order and 3 bytes per pixel.
  frame_buffer[pixel_offset + 0] = b;
  frame_buffer[pixel_offset + 1] = g;
  frame_buffer[pixel_offset + 2] = r;
}
