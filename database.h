#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QDateTime>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "variable.h"



class Database
{
public:
    Database();

    /* Destructor */
    ~Database();

    void test_database();

    /* Set connection */
    void setConnection(DbVar *VariableDB);

    /* Close connection maybe should be inserted on Destructor*/
    void closeConnection();

    /* Variable for database connection */

public:

};

#endif // DATABASE_H
