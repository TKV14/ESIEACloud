#ifndef _PAGE_H
#define _PAGE_H

void selector();
void selectPage(char *request);
void generatePage();
void createCookie();
void sendPage(char *page);
void sendFile(FILE *file);
void selectFile(char *filename);
void deleteFile(char *filename);
void sendHeader();
void validAuth(char *authType);

#endif /* _PAGE_H */
