#include <fcgi_stdio.h>
#include <stdlib.h>

#include "libpq-fe.h"

extern char **environ;

void select_page(char *page);
int check_login(char *login, char *password);
int logged();
void create_cookie(char *login, char *password);
void parseur_html(char *filename);
void send_SQL_command(PGconn *conn, char *command);
PGconn *connect_SQL_db();

int main(void)
{
	char **initialEnv = environ;

	while(FCGI_Accept() >= 0)
	{
		char page[255];

		printf("Content-type: text/html\r\n");

		select_page(page);		
		parseur_html(page);
	}
	return 0;
}

void select_page(char *page)
{
	char tmp[255], q_page[255], *http_referer, *server_addr, *query_string;

	query_string = getenv("QUERY_STRING");
	http_referer = getenv("HTTP_REFERER");
	server_addr = getenv("SERVER_ADDR");

	sscanf(query_string, "page=%s", q_page);
	sprintf(tmp, "https://%s/", server_addr);

	if(http_referer != NULL && server_addr != NULL)
	{
		if(logged() == 1)
		{
			if(strcmp(http_referer, tmp) == 0)
				sprintf(page, "/var/www/main.html");
			if(strcmp(q_page, "main") == 0)
				sprintf(page, "/var/www/main.html");
		}
		else
			sprintf(page, "/var/www/index.html");
	}
	else
	{
		if(logged() == 1)
			sprintf(page, "/var/www/main.html");
		else
			sprintf(page, "/var/www/index.html");
	}
}

int check_login(char *login, char *password)
{
	int rec_count;
	char password_bdd[255], sql_command[512];
	PGconn *conn = NULL;
	PGresult *res = NULL;

	sprintf(sql_command, "SELECT password FROM users WHERE login='%s';", login);

	conn = connect_SQL_db();
	res = PQexec(conn, sql_command);
	rec_count = PQntuples(res);

	if(rec_count == 1)
	{
		sprintf(password_bdd, "%s", PQgetvalue(res, 0, 0));

		if(strcmp(password, password_bdd) == 0)
			return 1;
	}

	return 0;
}

int logged()
{
	char login[255], password[255], *tmp_cookie;

	tmp_cookie = getenv("HTTP_COOKIE");

	if(tmp_cookie != NULL)
	{
		sscanf(tmp_cookie, "Session=login:%[^,],mdp:%s", &login, &password);
		return check_login(login, password);
	}
	else
	{
		int validate_user = 0;

		scanf("login=%[^&]&password=%s", &login, &password);

		validate_user = check_login(login, password);

		if(validate_user == 1)
		{
			create_cookie(login, password);
			return 1;
		}
		else
			return 0;
	}

	return 0;
}

void create_cookie(char *login, char *password)
{
	printf("Set-Cookie: Session=login:%s,mdp:%s;", login, password);
}

void parseur_html(char *filename)
{
	char tmp[1024];
	FILE *fichier = NULL;

	fichier = fopen(filename, "r");

	if(fichier != NULL)
	{
		while(fgets(tmp, sizeof(char) * 1024, fichier) != NULL)
			printf("%s", tmp);

		fclose(fichier);
	}
}

void send_SQL_command(PGconn *conn, char *command)
{
	PGresult *res;

	res = PQexec(conn, command);

	PQclear(res);
}

PGconn *connect_SQL_db()
{
	PGconn *conn;
	conn = PQsetdbLogin("localhost", "5432", NULL, NULL, "postgres", "postgres", "coco140690");

	return conn;
}
