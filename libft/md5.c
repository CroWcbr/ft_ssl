/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:34:39 by cdarrell          #+#    #+#             */
/*   Updated: 2022/12/22 21:50:18 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned int s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, \
							5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, \
							4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, \
							6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

static unsigned int K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, \
							0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, \
							0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, \
							0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, \
							0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, \
							0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, \
							0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, \
							0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, \
							0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, \
							0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, \
							0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, \
							0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, \
							0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, \
							0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, \
							0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, \
							0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

static unsigned char	*md5_update_str(const char *str, const uint64_t len, uint64_t new_len)
{
	unsigned char		*new_str;
	uint64_t			tmp;

	// printf("%ld\t%ld\n", len, new_len);

	new_str = malloc(new_len);
	if (!new_len)
		ft_error("Error malloc: md5 new_str");
	ft_memcpy(new_str, str, len);
	*(new_str + len) = 1 << 7;

// printf("%ld\t%ld\n", len, new_len);
	tmp = len + 1;
	while (tmp % 64 < 56)		//add 0 to 448 bit (56 byte)
		*(new_str + tmp++) = 0;
	// ft_memset(new_str + len + 1, 0, 56 - (len + 1) % 64);

// printf("%ld\t%ld\n", len, new_len);
	
	uint64_t tttttt = len * 8;
	ft_memcpy(new_str + new_len - 8, &tttttt, 8);	//len
	
// printf("%ld\t%ld\n", len, new_len);
	// tmp = (len + 1) % 64;
	// while (tmp < 56)		//add 0 to 448 bit (56 byte)
	// 	*(new_str + tmp++) = 0;
	// uint64_t tttttt = len * 8;
	// ft_memcpy(new_str + tmp, &tttttt, 8);	//len
	// printf("new_str = %s\n", new_str);
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
	return new_str;
}

void	md5(const char *str, const uint64_t len)
{
	uint64_t		new_len;
	unsigned char	*new_str;

	// new_len = ((len + 1) / 64 + 1) * 64;			//add 10000000 to end
	// if ((len + 1) % 64 > 56)
	// 	new_len += 64;								//add to 448 bit (56 byte)
	new_len = ((len + 1) / 64 + 1 + ((len + 1) % 64 > 56)) * 64;
	new_str = md5_update_str(str, len, new_len);

	unsigned int a0 = 0x67452301;
	unsigned int b0 = 0xefcdab89;
	unsigned int c0 = 0x98badcfe;
	unsigned int d0 = 0x10325476;

int kk = 0;
while (kk < new_len / 64)
{
	unsigned int A = a0;
	unsigned int B = b0;
	unsigned int C = c0;
	unsigned int D = d0;

	unsigned char M[16][4];
	for (int ii = 0; ii < 16; ii++)
	{
		M[ii][0] = *(new_str + kk*64 + ii * 4);
		M[ii][1] = *(new_str + kk*64 + ii * 4 + 1);
		M[ii][2] = *(new_str + kk*64 + ii * 4 + 2);
		M[ii][3] = *(new_str + kk*64 + ii * 4 + 3);
	}

	for (int i = 0; i < 64; i++)
	{
		unsigned int F;
		unsigned int g;

		if (i <= 15)
		{
            F = (B & C) | ((~B) & D);
            g = i;
		}
        else if (i <= 31)
		{
            F = (D & B) | ((~D) & C);
            g = (5*i + 1) % 16;
		}
        else if (i <= 47)
		{
            F = B ^ C ^ D;
            g = (3*i + 5) % 16;
		}
        else
		{
            F = C ^ (B | (~D));
            g = (7*i) % 16;
		}
		unsigned int n = (unsigned char)M[g][0] << 0 | (unsigned char)M[g][1] << 8 | (unsigned char)M[g][2] << 16 | (unsigned char)M[g][3] << 24;
		F = F + A + K[i] + n;
		A = D;
		D = C;
		C = B;
		B = B + (F << s[i] | F >> (32 - s[i]));
	}
	a0 = a0 + A;
	b0 = b0 + B;
	c0 = c0 + C;
	d0 = d0 + D;
	kk++;
}
	unsigned int tmp = a0;
	printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = b0;
	printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = c0;
	printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = d0;
	printf("%02x %02x %02x %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	printf("\n");
}
