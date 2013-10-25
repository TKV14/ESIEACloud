#include "main.h"

int authLogin(char *login, char *password)
{
	int rec_count;
	char passwordBdd[64], sqlCommand[512];
	PGconn *conn = NULL;
	PGresult *res = NULL;

	sprintf(sqlCommand, "SELECT password FROM users WHERE login='%s';", login);

	conn = connectSqlDb();
	res = PQexec(conn, sqlCommand);
	rec_count = PQntuples(res);

	if(rec_count == 1)
	{
		sprintf(passwordBdd, "%s", PQgetvalue(res, 0, 0));

		if(strcmp(password, passwordBdd) == 0)
			return 1;
	}

	return 0;
}

void sendSqlCommand(PGconn *conn, char *command)
{
	PGresult *res;

	res = PQexec(conn, command);

	PQclear(res);
}

PGconn *connectSqlDb()
{
	PGconn *conn;

	conn = PQsetdbLogin(DBHOST, DBPORT, NULL, NULL, DBNAME, DBLOGIN, DBPASS);

	return conn;
}
