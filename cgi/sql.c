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
		{
			PQfinish(conn);
			return 1;
		}
	}

//	PQfinish(conn);

	return 0;
}

int addUser(char *login, char *password)
{
	int rec_count;
	char sqlCommand[512];
	PGconn *conn = NULL;
	PGresult *res = NULL;

	conn = connectSqlDb();

	sprintf(sqlCommand, "SELECT * FROM users WHERE login='%s';", login);
	res = PQexec(conn, sqlCommand);
	rec_count = PQntuples(res);

	if(rec_count != 0)
	{
		fprintf(stderr, "l'utilisateur %s existe deja\n", login);
		return -1;
	}

	sprintf(sqlCommand, "INSERT INTO users VALUES ('%s', '%s');", login, password);
	sendSqlCommand(conn, sqlCommand);

//	PQfinish(conn);

	return 0;
}

void addCookie(char *login, char *cookie)
{
	int rec_count;
	char sqlCommand[512];
	PGconn *conn = NULL;
	PGresult *res = NULL;

	conn = connectSqlDb();

	sprintf(sqlCommand, "SELECT login FROM sessions WHERE idsession = '%s'", cookie);
	res = PQexec(conn, sqlCommand);
	rec_count = PQntuples(res);

	if(rec_count != 0)
	{
		sprintf(sqlCommand, "DELETE FROM sessions WHERE idsession = '%s'", cookie);
		sendSqlCommand(conn, sqlCommand);
	}

	sprintf(sqlCommand, "INSERT INTO sessions VALUES ('%s', '%s');", cookie, login);
	sendSqlCommand(conn, sqlCommand);

//	PQfinish(conn);
}

int validCookie(char *cookie)
{
	int rec_count;
	char sqlCommand[512];
	PGconn *conn = NULL;
	PGresult *res = NULL;

	conn = connectSqlDb();

	sprintf(sqlCommand, "SELECT login FROM sessions WHERE idsession = '%s'", cookie);

	res = PQexec(conn, sqlCommand);
	rec_count = PQntuples(res);

	if(rec_count == 1)
	{
		sprintf(actualSession->login, "%s", PQgetvalue(res, 0, 0));
//		PQfinish(conn);
		return 1;
	}
	else if(rec_count > 1)
	{
		sprintf(sqlCommand, "DELETE FROM sessions WHERE idsession = '%s'", actualSession->login);
		sendSqlCommand(conn, sqlCommand);
//		PQfinish(conn);
		return -1;
	}
	else
		return -1;
}

void deleteCookie()
{
	char sqlCommand[512];
	PGconn *conn = NULL;

	conn = connectSqlDb();

	sprintf(sqlCommand, "DELETE FROM sessions WHERE login = '%s'", actualSession->login);
	sendSqlCommand(conn, sqlCommand);
//	PQfinish(conn);
}

void sendSqlCommand(PGconn *conn, char *command)
{
	PGresult *res;

	res = PQexec(conn, command);

	PQclear(res);
//	PQfinish(conn);
}

PGconn *connectSqlDb()
{
	PGconn *conn;

	conn = PQsetdbLogin(DBHOST, DBPORT, NULL, NULL, DBNAME, DBLOGIN, DBPASS);

	return conn;
}
