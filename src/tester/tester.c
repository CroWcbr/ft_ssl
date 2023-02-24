#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/whrlpool.h>

uint8_t		*md5_main(const char *str, const uint64_t len);
uint8_t		*sha256_main(const char *str, const uint64_t len);
uint8_t		*sha512_main(const char *str, const uint64_t len);
uint8_t		*whirlpool(const char *str, const uint64_t len);

static unsigned char *WHIRLPOOL_EDIT(const unsigned char *str, size_t len,  unsigned char *str_openssl)
{
	return WHIRLPOOL(str, strlen(str), str_openssl);
}

static void	tester(char *hash, int hash_len, int test, int print, \
					unsigned char * (*openssl_hash)(const unsigned char *, size_t,  unsigned char *), \
					uint8_t* (*my_hash)(const char *, const uint64_t))
{
	int			err = 0;
	char		str[test];
	uint8_t		str_openssl[hash_len];
	uint8_t		*str_my;

	for (int i = 0; i <= test; i++)
		str[i] = 0;
	for (int i = 0; i < test; i++)
	{
		char random = rand() % 94 + 32;
		str[i] = random;
		// str[i] = '1';
		openssl_hash(str, strlen(str), str_openssl);
		str_my = my_hash(str, strlen(str));

		if (print == 1)
		{
			printf("%d\t|%s|\n", i, str);

			printf("MD5 openssl: \t");
			for(int i = 0; i < hash_len; i++)
				printf("%02x", str_openssl[i]);
			printf("\n");

			printf("MD5 my func: \t");
			for(int i = 0; i < hash_len; i++)
				printf("%02x", str_my[i]);
			printf("\n");
		}
		for (int j = 0; j < hash_len; j++)
			if (str_openssl[j] != str_my[j])
			{
				err++;
				break;
				// exit(0);
			}
		free(str_my);
	}
	printf("-------------------------------------\n");
	printf("\tError in test %s: %d\n", hash, err);
	printf("-------------------------------------\n");
}

int main()
{
	int test = 100;
	int print = 0;
	srand(time(NULL));
	tester("md5", MD5_DIGEST_LENGTH, test, print, MD5, md5_main);
	tester("sha256", SHA256_DIGEST_LENGTH, test, print, SHA256, sha256_main);
	tester("sha512", SHA512_DIGEST_LENGTH, test, print, SHA512, sha512_main);
	tester("whirlpool", WHIRLPOOL_DIGEST_LENGTH, test, print, WHIRLPOOL_EDIT, whirlpool);

	return (0);
}
