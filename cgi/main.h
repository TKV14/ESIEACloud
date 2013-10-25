#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sql.h"
#include "dir.h"
#include "page.h"
#include "crypto.h"

#define HEADERLENGTH 2048

typedef struct infos
{
	char login[64];
	char header[HEADERLENGTH];
}infos;

typedef infos* session;

int userId();
int checkString(char *string, int maxLength);
int rawToText(char *raw, char *out);

session actualSession;
