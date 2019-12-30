/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 13:17:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "point.h"
#include "mlx.h"

static int calc_julia(t_env *env, t_complex c, t_p2i cur)
{
	int i;
	t_complex z;
	t_complex t;

	//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
	z.r = (cur.x - env->width / 2) / (0.5 * env->zoom * env->width) + env->move_x;
	z.i = (cur.y - env->height / 2) / (0.5 * env->zoom * env->width) + env->move_y;
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

void	*plot_julia(void *env_ptr)
{
	t_env *env;
	t_p2i cur;
	t_complex c;
	int i;
	env = (t_env*)env_ptr;

	c.r = -0.7; //ft_map_range(env->mouse_x, ft_make_pair_d(0.0, width), ft_make_pair_d(-1.0, 1.0));
	c.i = 0.27015; //ft_map_range(env->mouse_y, ft_make_pair_d(0.0, height), ft_make_pair_d(-1.0, 1.0));
	cur.y = env->thread_range_start;
	while(cur.y < env->thread_range_end)
	{
		cur.x = 0;
		while(cur.x < env->width)
		{
			i = calc_julia(env, c, cur);
			if (i != MAX_ITER)
				put_pixel_mlx_img(env->fractal_img, cur.x, cur.y, get_color(i, env->color_palette));
			else
				put_pixel_mlx_img(env->fractal_img, cur.x, cur.y, 0);
			cur.x++;
  		}
		cur.y++;
	}
	return (env_ptr);
}


