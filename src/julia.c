/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:27:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 17:39:08 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "point.h"
#include "mlx.h"

static int	calc_julia(t_env *env, t_complex c, t_p2i cur)
{
	t_complex	z;
	t_complex	t;
	int			i;

	z.r = (cur.x - env->width / 2) / (0.5 * env->zoom * env->width) + env->move_x;
	z.i = (cur.y - env->height / 2) / (0.5 * env->zoom * env->width) + env->move_y;
	i = 0;
	while (i < env->iterations)
	{
		t.r = z.r;
		t.i = z.i;
		z.r = t.r * t.r - t.i * t.i + c.r;
		z.i = 2 * t.r * t.i + c.i;
		if ((z.r * z.r + z.i * z.i) > 4)
			break ;
		i++;
	}
	return (i);
}

void		*plot_julia(void *env_ptr)
{
	t_env		*env;
	t_p2i		cur;
	t_complex	c;
	int			i;

	env = (t_env*)env_ptr;
	c.r = env->free_julia ? ft_map_range(env->mouse_x,
		ft_make_pair_d(0.0, env->width), ft_make_pair_d(-1.0, 1.0)) : -0.7;
	c.i = env->free_julia ? ft_map_range(env->mouse_y,
		ft_make_pair_d(0.0, env->height), ft_make_pair_d(-1.0, 1.0)) : 0.27015;
	cur.y = env->thread_range_start;
	while (cur.y < env->thread_range_end)
	{
		cur.x = 0;
		while (cur.x < env->width)
		{
			i = calc_julia(env, c, cur);
			put_pixel_mlx_img(env->fractal_img, cur.x, cur.y, get_color(i, env->iterations, env->color_palette));
			cur.x++;
		}
		cur.y++;
	}
	return (env_ptr);
}
