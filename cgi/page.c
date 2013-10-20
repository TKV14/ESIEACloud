#include "main.h"

void selector()
{
	char request[255];
	char *queryString = NULL;

	request[0] = '\0';
	queryString = getenv("QUERY_STRING");
	if(queryString != NULL && queryString[0] != '\0')
	{
		if(sscanf(queryString, "page=%s", request) == 1)
			selectPage(request);
		else if(sscanf(queryString, "file=%s", request) == 1)
			selectFile(request);
		else
			fprintf(stderr, "ça merdouille sur la query string\n");
	}
	else
	{
		fprintf(stderr, "Direction page principale");
		selectPage("");
	}
}

void selectPage(char *request)
{
	char page[255];

	fprintf(stderr, "Request: %s\n", request);

	fflush(stderr);

	if(strcmp(request, "main") == 0)
		sprintf(page, "/var/www/main.html");
	else if(actualSession->login[0] != '\0')
		sprintf(page, "/var/www/main.html");
	else
		sprintf(page, "/var/www/index.html");

	fprintf(stderr, "login: %s\nPage choisie: %s\n", actualSession->login, page);

	generatePage(page);
}

void generatePage(char *page)
{
	char tmp[1024], data[65536];
	FILE *file = NULL;

	data[0] = '\0';

	file = fopen(page, "r");
	if(file == NULL)
	{
		fprintf(stderr, "hey mec j'trouve pas la page\n");

		file = fopen("/var/www/404.html", "r");
		if(file == NULL)
		{
			fprintf(stderr, "La page 404 n'a pas été trouvée\n");
			return;
		}
	}

	while(fgets(tmp, sizeof(char) * 1024, file) != NULL)
	{
		if(strstr(tmp, "<filelist>") != NULL)
		{
			strcat(data, print_folder("/ESIEACloud/tkv"));
		}
		else if(strstr(tmp, "</filelist>") != NULL)
		{
		}
		else
		{
			strcat(data, tmp);
		}
	}

	sprintf(actualSession->header, "Content-type: text/html\r\nContent-length: %d\r\n\r\n", strlen(data));
	sendHeader();

	sendPage(data);
}

void createCookie()
{
	printf("Content-Type: text/html\r\n");
	printf("Set-Cookie: Session=%s;\r\n", actualSession->login);
//	printf("Location: /\r\n");
//	printf("\r\n");
//	fflush(stdout);
}

void sendPage(char *page)
{
	printf("%s", page);
	fflush(stdout);
}

void selectFile(char *filename)
{
	int filesize;
	char path[255];
	FILE *file;
	if(filename == NULL)
		return;

	sprintf(path, "/ESIEACloud/%s/%s", actualSession->login, filename);

	fprintf(stderr, "path: %s\n", path);

	file = fopen(path, "r");
	if(file == NULL)
		fprintf(stderr, "Ah bah le fichier ne s'ouvre pas\n");
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);

	if(file == NULL)
		sprintf(actualSession->header, "Content-Type: text/html\r\n\r\nFile Not Found");
	else
		sprintf(actualSession->header, "Content-Description: File Transfer\r\n"
						"Content-Type: application/octet-stream\r\n"
						"Content-Disposition: attachment; filename=%s\r\n"
						"Content-Transfer-Encoding: binary\r\n"
						"Expires: 0\r\n"
						"Cache-Control: must-revalidate, post-check=0, pre-check=0\r\n"
						"Pragma: public\r\nContent-Length: %d\r\n"
						"\r\n", filename, filesize
						);

	sendHeader();
	sendFile(file);
}

void sendFile(FILE *file)
{
	char tmp;

	while(fread(&tmp, sizeof(char), 1, file) != 0)
		printf("%c", tmp);

	fclose(file);
}

void sendHeader()
{
	printf("%s", actualSession->header);
	fflush(stdout);
}
