/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:34:39 by cdarrell          #+#    #+#             */
/*   Updated: 2023/01/24 23:32:22 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static uint8_t	*md5_update_str(const char *str, \
				const uint64_t len, uint64_t *new_len)
{
	uint8_t				*new_str;
	uint64_t			len_64_bit;

	*new_len = ((len + 1) / 64 + 1 + ((len + 1) % 64 > 56)) * 64;
	new_str = malloc(*new_len);
	if (!new_str)
		ft_err("Error malloc: md5 new_str");
	ft_bzero(new_str, (size_t)(*new_len));
	ft_memcpy(new_str, str, len);
	ft_memset(new_str + len, 1 << 7, 1);
	len_64_bit = len * 8;
	ft_memcpy(new_str + *new_len - 8, &len_64_bit, 8);

	// int j = 0;
	// while (j < 128)
	// {
	// 	int i = 7;
	// 	printf("%d\t%d\t", j, (int)new_str[j]);
	// 	while (i >= 0)
	// 	{
	// 		printf("%d", (new_str[j] & (1 << i)) >> i);
	// 		i--;
	// 	}
	// 	printf("\n");
	// 	j++;
	// }

	return (new_str);
}

void	md5_algo(const uint8_t *new_str, \
		const uint64_t new_len, uint32_t *md_buf, uint32_t *md)
{
	int			kk;
	uint32_t	F;
	uint32_t	g;

	kk = 0;
	while (kk < new_len / 64)
	{
		md[A] = md_buf[A];
		md[B] = md_buf[B];
		md[C] = md_buf[C];
		md[D] = md_buf[D];
		for (int i = 0; i < 64; i++)
		{
			if (i <= 15)
			{
				F = (md[B] & md[C]) | ((~md[B]) & md[D]);
				g = i;
			}
			else if (i <= 31)
			{
				F = (md[D] & md[B]) | ((~md[D]) & md[C]);
				g = (5 * i + 1) % 16;
			}
			else if (i <= 47)
			{
				F = md[B] ^ md[C] ^ md[D];
				g = (3 * i + 5) % 16;
			}
			else
			{
				F = md[C] ^ (md[B] | (~md[D]));
				g = (7 * i) % 16;
			}
			uint32_t M[16];
			for (int ii = 0; ii < 16; ii++)
				M[ii] = *(new_str + kk * 64 + ii * 4) << 0 | \
						*(new_str + kk * 64 + ii * 4 + 1) << 8 | \
						*(new_str + kk * 64 + ii * 4 + 2) << 16 | \
						*(new_str + kk * 64 + ii * 4 + 3) << 24;
			F = F + md[A] + K[i] + M[g];
			md[A] = md[D];
			md[D] = md[C];
			md[C] = md[B];
			md[B] += F << s[i] | F >> (32 - s[i]);
		}
		md_buf[A] += md[A];
		md_buf[B] += md[B];
		md_buf[C] += md[C];
		md_buf[D] += md[D];
		kk++;
	}
}

void	md5(const char *str, const uint64_t len)
{
	uint8_t			*new_str;
	uint64_t		new_len;
	uint32_t		md_buf[4];
	uint32_t		md[4];

	new_str = md5_update_str(str, len, &new_len);
	md_buf[A] = 0x67452301;
	md_buf[B] = 0xefcdab89;
	md_buf[C] = 0x98badcfe;
	md_buf[D] = 0x10325476;
	md5_algo(new_str, new_len, md_buf, md);

	uint8_t	digist[16];
	ft_memcpy(digist + 0, &md_buf[A], 4);
	ft_memcpy(digist + 4, &md_buf[B], 4);
	ft_memcpy(digist + 8, &md_buf[C], 4);
	ft_memcpy(digist + 12, &md_buf[D], 4);
	for (int iii = 0; iii < 16; iii++)
		printf("%02x ", digist[iii]);
	printf("\n");
}
