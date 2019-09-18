#include "database.h"
#include "variable.h"


Database::Database()
{

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

void Database::setConnection(DbVar *VariableDB)
{
    //db.addDatabase("QMYSQL");

}

