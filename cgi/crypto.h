#ifndef _CRYPTO_H
#define _CRYPTO_H

#include <openssl/sha.h>

void encryptSha256(const char *chaine, const char *salt, const char *alea, char *encryptData);

#endif /* _CRYPTO_H */
