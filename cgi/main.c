#include "main.h"

int main(void)
{
	actualSession = malloc(sizeof(session));

	while(FCGI_Accept() >= 0)
	{
		switch(userId())
		{
			case 0:
				createCookie();
				selectPage("main");
				break;
			case 1:
			case 2:
				selector();
				break;
		}
	}

	return 0;
}

int userId()
{
	int i;
	char *cookie, login[64], password[64];
	actualSession->login[0] = '\0';
	actualSession->header[0] = '\0';

	cookie = getenv("HTTP_COOKIE");
	if(cookie != NULL)
	{
//		fprintf(stderr, "Y'a un cookie YOUPI: %s\n", cookie);
		sscanf(cookie ,"Session=%s", actualSession->login);
		fprintf(stderr, "Login: %s\n", actualSession->login);
		return 1;
	}
	else
	{
		if(scanf("login=%[^&]&password=%s", login, password) == 2)
		{
			fprintf(stderr, "login: %s, pass: %s\n", login, password);

			if(strnlen(login, 64) > 63)
			{
				fprintf(stderr, "Login is too long\n");
				return -1;
			}
			if(strnlen(password, 64) > 63)
			{
				fprintf(stderr, "Password is too long\n");
				return -1;
			}

			i=0;
			while(login[i] != '\0')
			{
				if(!(	((login[i] >= 48) && (login[i] <= 57)) ||
					((login[i] >= 65) && (login[i] <= 90)) ||
					((login[i] >= 97) && (login[i] <= 122))
					))
				{
					fprintf(stderr, "Bad login %d, %c\n", i, login[i]);
					return -2;
				}

				i++;
			}

			i=0;
			while(password[i] != '\0')
			{
				if(!(	((password[i] >= 48) && (password[i] <= 57)) ||
					((password[i] >= 65) && (password[i] <= 90)) ||
					((password[i] >= 97) && (password[i] <= 122))
					))
				{
					fprintf(stderr, "Bad password\n");
					return -1;
				}

				i++;
			}

			fprintf(stderr, "login: %s\n", login);

			sprintf(actualSession->login, "%s", login);
//			strcpy(actualSession->login, login);

			return 0;
		}
		else
			return 2;
	}

	return 1;
}
