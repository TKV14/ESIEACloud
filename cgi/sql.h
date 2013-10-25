#ifndef _SQL_H
#define _SQL_H

#define DBNAME "postgres"
#define DBLOGIN "postgres"
#define DBPASS "aucun"
#define DBHOST "localhost"
#define DBPORT "5432"

#include <libpq-fe.h>

int authLogin(char *login, char *password);
void sendSqlCommand(PGconn *conn, char *command);
PGconn *connectSqlDb();

#endif
