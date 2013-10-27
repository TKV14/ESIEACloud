#include "main.h"

int main(void)
{
	int retour;
	actualSession = malloc(sizeof(session));

	while(FCGI_Accept() >= 0)
	{
		switch((retour = userId()))
		{
			case 0:
				createCookie();
				selectPage("main");
				break;
			case 1:
				selector();
				break;
			case -1:
			case 2:
				selectPage("index");
				break;
		}
	}

	return 0;
}

int userId()
{
	char sessionCookie[64], authType[16];
	char *cookie, *queryString;
	actualSession->login[0] = '\0';
	actualSession->header[0] = '\0';

	cookie = getenv("HTTP_COOKIE");
	if(cookie != NULL)
	{
		sscanf(cookie ,"Session=%s", sessionCookie);
		if(validCookie(sessionCookie) == 1)
		{
			fprintf(stderr, "Non null cookie Login: %s\n", actualSession->login);
			queryString = getenv("QUERY_STRING");
			if(sscanf(queryString, "auth=%s", authType) == 1)
			{
				if(strcmp(authType, "logout") == 0)
				{
					if(actualSession->login[0] != '\0')
					{
						deleteCookie();
						actualSession->login[0] = '\0';
					}
					selectPage("index");
					return 1;
				}
			}

			return 1;
		}
		else
		{
			fprintf(stderr, "Cookie non valide\n");
			return auth();
		}
	}
	else
		return auth();

	return 1;
}

int auth()
{
	char login[64], password[64], encryptPassword[64], rawLogin[512], rawPassword[512], authType[16];
	char *queryString;

	queryString = getenv("QUERY_STRING");
	if(sscanf(queryString, "auth=%s", authType) != 1)
		return 2;

	if(scanf("login=%[^&]&password=%[^&]", rawLogin, rawPassword) == 2)
	{
		rawToText(rawLogin, login);
		rawToText(rawPassword, password);

		fprintf(stderr, "Login: %s, Pass: %s\n", login, password);

		if(checkString(login, 64) != 1)
		{
			fprintf(stderr, "Probleme Login\n");
			return -1;
		}
		if(checkString(password, 64) != 1)
		{
			fprintf(stderr, "Probleme password\n");
			return -1;
		}

		if(strcmp(authType, "login") == 0)
		{
			encryptSha256(password, NULL, NULL, encryptPassword);
			if(authLogin(login, encryptPassword) == 1)
			{
				sprintf(actualSession->login, "%s", login);
				return 0;
			}
			else
			{
				fprintf(stderr, "Auth Failed\n");
				selectPage("index");
				return 2;
			}
		}
		else if(strcmp(authType, "inscription") == 0)
		{
			encryptSha256(password, NULL, NULL, encryptPassword);
			if(createUser(login, encryptPassword) == 0)
			{
				sprintf(actualSession->login, "%s", login);
				return 0;
			}
			else
				return 2;
		}
		else
		{
			fprintf(stderr, "c'est pas bon\n");
			return 2;
		}
	}
	else
		return 2;

	return 1;
}

int createUser(char *login, char *password)
{
	char dossier[256];

	if(addUser(login, password) == -1)
		return -1;

	sprintf(dossier, "/ESIEACloud/%s/", login);

	fprintf(stderr, "Dossier: %s\n", dossier); 

	if(mkdir(dossier, S_IWUSR | S_IRUSR | S_IXUSR) == -1)
	{
		fprintf(stderr, "%s", strerror(errno));
		return -2;
	}

	return 0;
}

int checkString(char *string, int maxLength)
{
	int i;

	if(((int)strnlen(string, maxLength)) > (maxLength-1))
	{
		fprintf(stderr, "La chaine est trop longue\n", string);
		return -1;
	}

	i=0;
	while(string[i] != '\0')
	{
		if(	(string[i] == '\x00') ||
			(string[i] == '\n') ||
			(string[i] == '\r') ||
			(string[i] == '\\') ||
			(string[i] == '\'') ||
			(string[i] == '\"') ||
			(string[i] == '\x1a')
			)
		{
			fprintf(stderr, "Caractere interdit detecte\n");
			return -2;
		}

		i++;
	}

	return 1;
}

int rawToText(char *raw, char *out)
{
	int i, j, code;
	char c = '\0';
	char hex[3];

	i=0;
	j=0;
	while(raw[i] != '\0')
	{
		if(raw[i] == '%')
		{
			strncpy(hex, &raw[i+1], 2);
			hex[3] = '\0';
			code = (int) strtol(hex, '\0', 16);

			switch(code)
			{
				case 34:	c = '"'; break;
				case 35:	c = '#'; break;
				case 36:	c = '$'; break;
				case 37:	c = '%'; break;
				case 38:	c = '&'; break;

				case 43:	c = '+'; break;
				case 44:	c = ','; break;

				case 47:	c = '/'; break;

				case 58:	c = ':'; break;
				case 59:	c = ';'; break;
				case 60:	c = '<'; break;
				case 61:	c = '='; break;
				case 62:	c = '>'; break;
				case 63:	c = '?'; break;
				case 64:	c = '@'; break;

				case 91:	c = '['; break;
				case 92:	c = '\\'; break;
				case 93:	c = ']'; break;
				case 94:	c = '^'; break;

				case 96:	c = '\''; break;

				case 123:	c = '{'; break;
				case 124:	c = '|'; break;
				case 125:	c = '}'; break;
				case 126:	c = '~'; break;

				default:	fprintf(stderr, "Unknow caracter\n"); return -1;
			}

			out[j] = c;
			i+=2;
		}
		else
			out[j] = raw[i];

		i++;
		j++;
	}

	out[j] = '\0';

	return 1;
}
