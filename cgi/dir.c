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
		sprintf(tmp, "<div><a href=\"/?file=%s\">%s</a></div>\n", contenu[i], contenu[i]);
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
