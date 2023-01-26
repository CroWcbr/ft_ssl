/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:34:39 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/27 02:16:53 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static void	md5_init(t_md5 *md5, const char *str, const uint64_t *len)
{
	md5->str = (uint8_t *)str;
	md5->len = *len;
	md5->pos = 0;
	md5->len_64_bit = md5->len * 8;
	md5->md_buf[A] = 0x67452301;
	md5->md_buf[B] = 0xefcdab89;
	md5->md_buf[C] = 0x98badcfe;
	md5->md_buf[D] = 0x10325476;
	md5->result = malloc(16 * (sizeof(uint8_t)));
	if (!md5->result)
		ft_err("Error malloc: md5.c - md5_init - md5->result");
}

static void	md5_update(t_md5 *md5)
{
	while (md5->len - md5->pos > 64)
	{
		md5_algorithm(md5->str + md5->pos, md5->md_buf, md5->md_tmp);
		md5->pos += 64;
	}
}

static void	md5_final(t_md5 *md5)
{
	uint8_t				*new_str;
	uint64_t			new_len;
	uint64_t			pos;

	new_len = ((md5->len - md5->pos + 1) / 64 + 1 + \
				((md5->len -  md5->pos + 1) % 64 > 56)) * 64;
	new_str = malloc(new_len);
	if (!new_str)
		ft_err("Error malloc: md5.c - md5_update - new_str");
	ft_bzero(new_str, (size_t)(new_len));
	ft_memcpy(new_str, md5->str +  md5->pos, md5->len -  md5->pos);
	ft_memset(new_str + md5->len -  md5->pos, 1 << 7, 1);
	ft_memcpy(new_str + new_len - 8, &md5->len_64_bit, 8);
	pos = 0;
	while (new_len > pos)
	{
		md5_algorithm(new_str + pos, md5->md_buf, md5->md_tmp);
		pos += 64;
	}
	free(new_str);
}

uint8_t	*md5_main(const char *str, const uint64_t len)
{
	t_md5			md5;

	md5_init(&md5, str, &len);
	md5_update(&md5);
	md5_final(&md5);

	ft_memcpy(md5.result + 0, &md5.md_buf[A], 4);
	ft_memcpy(md5.result + 4, &md5.md_buf[B], 4);
	ft_memcpy(md5.result + 8, &md5.md_buf[C], 4);
	ft_memcpy(md5.result + 12, &md5.md_buf[D], 4);
	return md5.result;
}
