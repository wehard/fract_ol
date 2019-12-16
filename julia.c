/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/16 17:45:14 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "point.h"
#include "mlx.h"

static int			get_color(int i)
{
	return (i << 16 | i << 8 | i);
}

static int calc_julia(t_mlx_data *mlx_data, t_complex c)
{
	int i;
	t_complex z;
	double temp;


	// x = ((x / W) * win->size) + win->center_x - (win->size * 0.5);
	// y = ((y / W) * win->size) + win->center_y - (win->size * 0.5);
	// re = (((D)win->mous->x - (D)(WINDOW_SIZE / 2)) / (D)W);
	// im = (((D)win->mous->y - (D)(WINDOW_SIZE / 2)) / (D)W);
	c.r = (c.r / (float)WIN_W) + 640.0f - ((float)WIN_W * 0.5);
	c.i = (c.i / (float)WIN_H) + 360.0f - ((float)WIN_H * 0.5);
	z.r = ((double)mlx_data->mouse_x - (double)(WIN_W / 2)) / (double)WIN_W;
	z.i = ((double)mlx_data->mouse_y - (double)(WIN_H / 2)) / (double)WIN_H;
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

void	plot_julia(t_mlx_data *mlx_data, float width, float height)
{
	t_p2i cur;
	t_complex c;
	int i;

	cur.y = 0;
	while (cur.y < height)
	{
		cur.x = 0;
		while (cur.x < width)
		{
			c.r = ((cur.x - width / 2.0) * 4.0 / width);
			c.i = ((cur.y - height / 2.0) * 4.0 / width);
			i = calc_julia(mlx_data, c);
			mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, cur.x, cur.y, get_color(i));
			cur.x++;
		}
		cur.y++;
	}


}
