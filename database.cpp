#include "database.h"

Database::Database()
{
    /* Database constructor with no argv (argc=1)*/
    qDebug()<<"Constructor";
    this->hostname="localhost";
    this->username="root";
    this->password="";
    this->port=3306;
    this->database="testdb";

}

Database::Database(QString s_username, QString s_password, QString s_database)
{
    /* assign to variable */
    this->hostname="localhost";
    this->username=s_username;
    this->password=s_password;
    this->port=3306;
    this->database=s_database;
}

Database::Database(QString s_hostname, int s_port, QString s_username, QString s_password, QString s_database)
{

    /* assign to variable */

    this->hostname=s_hostname;
    this->username=s_username;
    this->port=s_port;
    this->password=s_password;
    this->database=s_database;
}



Database::~Database()
{
    qDebug()<<"====================================";
    qDebug()<<" What of the meaning of destruction";

}

void Database::test_database()
{
    qDebug()<<"Database testing "<<endl;

}
