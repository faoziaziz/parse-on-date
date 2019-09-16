#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>

class Database
{
public:
    Database();
    Database (QString s_username, QString s_password, QString s_database);
    Database(QString s_hostname, int s_port, QString s_username, QString s_password, QString s_database);
    ~Database();
    void test_database();

    void setConnection();
    void closeConnection();

private:
    QString hostname;
    QString username;
    QString password;
    int port;
    QString database;

};

#endif // DATABASE_H
