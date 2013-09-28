#include <fcgi_stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "libpq-fe.h"

extern char **environ;

void print_folder(char *path);
void read_folder(char *path, char **contenu);
void select_page(char *page);
void file_download(char *user, char *file);
void get_login(char *login);
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

		page[0] = '\0';

		select_page(page);
		if(page[0] != '\0')
		{
			printf("Content-Type: text/html\r\n\r\n");
			parseur_html(page);
		}
	}
	return 0;
}

void print_folder(char *path)
{
	int i;
	char **contenu, login[255];

	contenu = (char **) malloc(sizeof(char*)*30);

	for(i=0; i<30; i++)
	{
		contenu[i] = (char *) malloc(sizeof(char)*128);
		contenu[i][0] = '\0';
	}

	get_login(login);

	printf("%s\n", login);

	sprintf(path, "/ESIEACloud/%s/", login);

	read_folder(path, contenu);

	i=0;

	while(contenu[i][0] != '\0')
	{
		printf("<div><a href=\"/cgi-bin/prog.fcgi?user=tkv&file=%s\">%s</a></div>", contenu[i], contenu[i]);
		i++;
	}
}

void read_folder(char *path, char **contenu)
{
	int i;
	struct dirent *lecture;
	DIR *rep;

	rep = opendir(path);

	i=0;

	while((lecture = readdir(rep)))
	{
		if(lecture->d_name[0] != '.')
		{
			if(lecture->d_type == 8)
			{
				strcpy(contenu[i], lecture->d_name);
				i++;
			}
		}
	}
}

void select_page(char *page)
{
	char tmp[255], q_page[255], user[255], file[255], *http_referer, *server_addr, *query_string;

	query_string = getenv("QUERY_STRING");
	http_referer = getenv("HTTP_REFERER");
	server_addr = getenv("SERVER_ADDR");

	user[0] = '\0';

	if(sscanf(query_string, "page=%s", q_page) == 0)
		sscanf(query_string, "user=%[^&]&file=%s", user, file);
	sprintf(tmp, "https://%s/", server_addr);

	if(http_referer != NULL && server_addr != NULL)
	{
		if(logged() == 1)
		{
			if(strcmp(http_referer, tmp) == 0)
				sprintf(page, "/var/www/main.html");
			if(strcmp(q_page, "main") == 0)
				sprintf(page, "/var/www/main.html");
			if(user[0] != '\0')
			{
				file_download(user, file);
			}
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

void file_download(char *user, char *file)
{
	int filesize;
	char filename[255], tmp;
	FILE *fichier = NULL;

	sprintf(filename, "/ESIEACloud/%s/%s", user, file);

	fichier = fopen(filename, "r");

	fseek(fichier, 0L, SEEK_END);
	filesize = ftell(fichier);
	fseek(fichier, 0L, SEEK_SET);

//	printf("Content-Type: text/html\r\n\r\n");

	if(fichier == NULL)
	{
		printf("Content-Type: text/html\r\n");
		printf("\r\n");
		printf("File Not Found: %s\n", file);
		return;
	}

	printf("Content-Description: File Transfer\r\n");
	printf("Content-Type: application/octet-stream\r\n");
	printf("Content-Disposition: attachment; filename=%s\r\n", file);
	printf("Content-Transfer-Encoding: binary\r\n");
	printf("Expires: 0\r\n");
	printf("Cache-Control: must-revalidate, post-check=0, pre-check=0\r\n");
	printf("Pragma: public\r\n");
	printf("Content-Length: %d\r\n", filesize);
	printf("\r\n");

	while(fread(&tmp, sizeof(char), 1, fichier) != 0)
	{
		printf("%c", tmp);
	}
}

void get_login(char *login)
{
	char *tmp_cookie;

	tmp_cookie = getenv("HTTP_COOKIE");

	if(tmp_cookie != NULL)
		sscanf(tmp_cookie, "Session=login:%[^,]", login);
	else
		sprintf(login, "null");
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
	printf("Set-Cookie: Session=login:%s,mdp:%s;\r\n", login, password);
}

void parseur_html(char *filename)
{
	char tmp[1024], path[255];
	FILE *fichier = NULL;

	fichier = fopen(filename, "r");

	if(fichier != NULL)
	{
		while(fgets(tmp, sizeof(char) * 1024, fichier) != NULL)
		{
			if(strstr(tmp, "<filelist>"))
			{
				sprintf(path, "/");
				print_folder(path);
			}
			else if(strstr(tmp, "</filelist>"))
			{
			}
			else
				printf("%s", tmp);
		}

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
