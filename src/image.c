/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 00:06:17 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 12:25:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"

t_mlx_img	*create_mlx_image(t_env *env, int width, int height)
{
	t_mlx_img *img;

	if (!(img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
	{
		ft_putendl_fd("error: create_mlx_image failed!", 2);
		return (NULL);
	}
	img->w = width;
	img->h = height;
	if (!(img->img = mlx_new_image(env->mlx->mlx_ptr, img->w, img->h)))
	{
		ft_putendl_fd("error: mlx_new_image failed!", 2);
		return (NULL);
	}
	if (!(img->d_addr = mlx_get_data_addr(img->img, &img->bpp,
										&img->size_line, &img->endian)))
	{
		ft_putendl_fd("error: mlx_get_data_addr failed!", 2);
		return (NULL);
	}
	img->bpp /= 8;
	return (img);
}

void		clear_mlx_img(t_mlx_img *img)
{
	if (!img || !img->d_addr)
		return ;
	ft_memset(img->d_addr, 0, img->w * img->h * img->bpp);
}

void		put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c)
{
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	*(int*)(img->d_addr + (((y * img->w) + x) * img->bpp)) = c;
}

void		draw_rect(t_mlx_img *img, t_p2i pos, t_p2i size, int color)
{
	t_p2i cur;

	cur.y = pos.y;
	while (cur.y < pos.y + size.y)
	{
		cur.x = pos.x;
		while (cur.x < pos.x + size.x)
		{
			put_pixel_mlx_img(img, cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
}
