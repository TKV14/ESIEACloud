#include "main.h"

void encryptSha256(const char *chaine, const char *salt, const char *alea, char *encryptData)
{
	int i;
	char tmp[3];
	char buffer[512];
	unsigned char out[32];
	SHA256_CTX ctx;

	memset(buffer, '\0', 64);
	strcpy(buffer, chaine);

	SHA256_Init(&ctx);

	SHA256_Update(&ctx, buffer, strlen(buffer));
	if(salt != NULL)
		SHA256_Update(&ctx, salt, strlen(salt));
	if(alea != NULL)
		SHA256_Update(&ctx, alea, strlen(alea));

	SHA256_Final(out, &ctx);

	encryptData[0] = '\0';

	for(i=0; i<32; i++)
	{
		tmp[0] = '\0';
		tmp[1] = '\0';
		tmp[2] = '\0';
		sprintf(tmp, "%02x", out[i]);
		strcat(encryptData, tmp);
	}

	encryptData[64] = '\0';
}
