#include <QCoreApplication>
#include <QDebug>
#include "database.h"


int main(int argc, char *argv[])
{
    /* Core application */
    QCoreApplication a(argc, argv);
    Database aksesdb;

    aksesdb.test_database();




    return a.exec();
}
