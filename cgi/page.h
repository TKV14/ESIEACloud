#ifndef _PAGE_H
#define _PAGE_H

void selector();
void selectPage();
void generatePage();
void createCookie();
void sendPage(char *page);
void sendFile(FILE *file);
void selectFile(char *filename);
void sendHeader();

#endif /* _PAGE_H */
