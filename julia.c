/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/17 20:32:45 by wkorande         ###   ########.fr       */
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

static int calc_julia(t_mlx_data *mlx_data, t_complex c, t_p2i cur)
{
	int i;
	t_complex z;
	t_complex t;

	//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
	z.r = (cur.x - WIN_W / 2) / (0.5 * mlx_data->zoom * WIN_W) + mlx_data->move_x;
	z.i = (cur.y - WIN_H / 2) / (0.5 * mlx_data->zoom * WIN_H) + mlx_data->move_y;
	//i will represent the number of iterations
	//start the iteration process
	i = 0;
	while(i < MAX_ITER)
	{
		//remember value of previous iteration
		t.r = z.r;
		t.i = z.i;
		//the actual iteration, the real and imaginary part are calculated
		z.r = t.r * t.r - t.i * t.i + c.r;
		z.i = 2 * t.r * t.i + c.i;
		//if the point is outside the circle with radius 2: stop
		if((z.r * z.r + z.i * z.i) > 4)
			break ;
		i++;
	}

	return (i);
}

void	plot_julia(t_mlx_data *mlx_data, float width, float height)
{
	t_p2i cur;
	t_complex c;
	int i;

	c.r = -0.7;
	c.i = 0.27015;
	cur.y = 0;
	while(cur.y < height)
	{
		cur.x = 0;
		while(cur.x < width)
		{
			i = calc_julia(mlx_data, c, cur);
			frame_buffer_set(mlx_data->frame_buffer, cur.x, cur.y, get_color(i));
			cur.x++;
  		}
		cur.y++;
	}
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
			mlx_data->frame_buffer->img, 0, 0);
}
