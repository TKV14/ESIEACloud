#include "main.h"

char *print_folder(char *path)
{
	int i;
	char tmp[1024];
	char *retour;
	char **contenu;

	contenu = (char **) malloc(sizeof(char*)*64);
	retour = (char *) malloc(sizeof(char)*16384);
	tmp[0] = '\0';
	retour[0] = '\0';

	for(i=0; i<30; i++)
	{
		contenu[i] = (char *) malloc(sizeof(char)*128);
		contenu[i][0] = '\0';
	}

	read_folder(path, contenu);

	i=0;

	while(contenu[i][0] != '\0')
	{
		sprintf(tmp, "<TR><TH><a href=\"/?file=%s\">%s</a></TH><TH></TH><TH></TH><TH></TH></TR>\n", contenu[i], contenu[i]);
		strcat(retour, tmp);
		i++;
	}

	return retour;
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

void upfile()
{
	int size = 1000000;
	char tmp[1000000];
	char filename[256], filepath[512];
	char null[512];
	char c1, c2;
	FILE *file = NULL;

	fgets(tmp, size, stdin);
	fgets(tmp, size, stdin);

	if(sscanf(tmp, "%s %s %s filename=\"%[^\"]", null, null, null, filename) == 4)
	{
		fprintf(stderr, "Felicitaion, c'est un beau fichier: %s\n", filename);
		fgets(tmp, size, stdin);

		sprintf(filepath, "/ESIEACloud/%s/%s", actualSession->login, filename);
		file = fopen(filepath, "w+");

		while(1)
		{
			fread(&c1, sizeof(char), 1, stdin);
			if(c1 == '\r')
			{
				fread(&c2, sizeof(char), 1, stdin);
				if(c2 == '\n')
					break;
			}
		}

		while(1)
		{
			fread(&c1, sizeof(char), 1, stdin);
			if(c1 == '\r')
			{
				fread(&c2, sizeof(char), 1, stdin);
				if(c2 == '\n')
					break;
				else
				{
					fwrite(&c1, sizeof(char), 1, file);
					fwrite(&c2, sizeof(char), 1, file);
				}
			}
			else
				fwrite(&c1, sizeof(char), 1, file);
		}

	}
}
