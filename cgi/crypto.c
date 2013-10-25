#include "main.h"

void encryptSha256(const char *chaine, const char *salt, const char *alea)
{
	int i;
	char buffer[512];
	unsigned char out[32];
	SHA256_CTX ctx;

	memset(buffer, '\0', 64);
	strcpy(buffer, in);

	SHA256_Init(&ctx);

	SHA256_Update(&ctx, buffer, strlen(buffer));
	if(salt != NULL)
		SHA256_Update(&ctx, salt, strlen(salt));
	if(alea != NULL)
		SHA256_Update(&ctx, alea, strlen(alea));

	SHA256_Final(out, &ctx);

	fprintf(stderr, "Sha: ");

	for(i=0; i<32; i++)
	{
		fprintf(stderr, "%02x", out[i]);
	}

	fprintf(stderr, "\n");
}
