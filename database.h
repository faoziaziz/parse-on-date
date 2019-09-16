#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>

class Database
{
public:
    Database();
    ~Database();
    void test_database();
private:
    QString hostname;
    QString username;
    QString password;
    int port;
    QString database;

};

#endif // DATABASE_H
