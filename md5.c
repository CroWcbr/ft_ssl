/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:34:39 by cdarrell          #+#    #+#             */
/*   Updated: 2022/08/08 22:23:23 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	md5(char *str)
{
	size_t len_bit = ft_strlen(str) * 8;
	size_t len_bit_plus_128 = len_bit + 8;
	size_t len_zero_448 = len_bit_plus_128;
	while (len_zero_448 % 64 < 56)
		len_zero_448++;
	
	char *tmp = (char *)malloc(64);
	ft_memcpy(tmp, str, ft_strlen(str));

	unsigned char test[2];
	test[0] = (unsigned char)128;
	test[1] = '\0';
	while (len_zero_448 % 64 < 56)
	{
		ft_memcpy(tmp + ft_strlen(str), test, 1);
	}


	ft_memcpy(tmp + ft_strlen(str) + 1, test, len_zero_448 / 8 - ft_strlen(str) - 1);
	ft_memcpy(tmp + len_zero_448, ft_strlen(str) * 8, 4);



	// std::vector<std::string>	M;
	// for (int i = 0; i < 64; i += 4)
	// {
	// 	std::string tmp = str.substr(i, 4);
	// 	unsigned int n = (unsigned char)tmp[0] << 0 | (unsigned char)tmp[1] << 8 | (unsigned char)tmp[2] << 16 | (unsigned char)tmp[3] << 24;
	// 	std::cout << i << " : " << n << std::endl;
	// 	M.push_back(str.substr(i, 4));
	// }

	unsigned int s[64] = {	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, \
							5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, \
							4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, \
							6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

	// Определяем таблицу констант следующим образом
	unsigned int K[64] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, \
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

	unsigned int a0 = 0x67452301;   // A
	unsigned int b0 = 0xefcdab89;   // B
	unsigned int c0 = 0x98badcfe;   // C
	unsigned int d0 = 0x10325476;   // D

	unsigned int A = a0;
	unsigned int B = b0;
	unsigned int C = c0;
	unsigned int D = d0;

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
		F = F + A + K[i] + n;  // M[g] — 32 битный блок
		A = D;
		D = C;
		C = B;
		B = B + (F << s[i] | F >> (32 - s[i])); // Выполняем битовый сдвиг
	}
	a0 = a0 + A;
	b0 = b0 + B;
	c0 = c0 + C;
	d0 = d0 + D;

	unsigned int tmp = a0;
	printf("%02x, %02x, %02x, %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = b0;
	printf("%02x, %02x, %02x, %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = c0;
	printf("%02x, %02x, %02x, %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	tmp = d0;
	printf("%02x, %02x, %02x, %02x", tmp % 256 , tmp / 256 % 256 , tmp / 256 / 256 % 256 , tmp / 256 /256 / 256 % 256);
	printf("\n");
}
