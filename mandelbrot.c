/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/16 15:56:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "point.h"
#include "mlx.h"

int			get_color(int i)
{
	return (i << 16 | i << 8 | i);
}

t_complex	make_complex(double r, double i)
{
	t_complex c;

	c.r = r;
	c.i = i;
	return (c);
}

static int calc_mandelbrot(t_complex c)
{
	int i;
	t_complex z;
	double temp;


	z.r = 0.0;
	z.i = 0.0;
	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < MAX_ITER)
	{
		temp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = temp;
		i++;
	}
	return (i);
}

void	plot_mandelbrot(t_mlx_data *mlx_data, float width, float height)
{
	t_p2i cur;
	t_complex c;
	int i;

	clear_frame_buffer(mlx_data->frame_buffer);
	cur.y = 0;
	while (cur.y < height)
	{
		cur.x = 0;
		while (cur.x < width)
		{
			c.r = (cur.x - mlx_data->mouse_x) * ((4.0*mlx_data->zoom_level) / width);
			c.i = (cur.y - mlx_data->mouse_y) * ((4.0*mlx_data->zoom_level) / width);
			i = calc_mandelbrot(c);
			frame_buffer_set(mlx_data->frame_buffer, cur.x, cur.y, get_color(i));
			cur.x++;
		}
		cur.y++;
	}
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
			mlx_data->frame_buffer->img, 0, 0);
}
