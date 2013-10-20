#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"
#include "page.h"

#define HEADERLENGTH 2048

typedef struct infos
{
	char login[64];
	char header[HEADERLENGTH];
}infos;

typedef infos* session;

int userId();

session actualSession;
