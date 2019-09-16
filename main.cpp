#include <QCoreApplication>
#include <QDebug>
#include "database.h"
#include "parsing.h"

int main(int argc, char *argv[])
{
    /* Core application */
    QCoreApplication a(argc, argv);
    Parsing AccParsing;
    AccParsing.test_parsing();



    return a.exec();
}
