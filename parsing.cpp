#include "parsing.h"

Parsing::Parsing()
{
    qDebug()<<"Parsing constructor";
}

Parsing::~Parsing()
{
    qDebug()<<"Parsing destructior";

}

void Parsing::test_parsing()
{
    QString test;
    QByteArray data;

    /* get file form database */
    qDebug()<<"Parsing tested";
    //aksesDB->setConnection();
    aksesDB->test_database();


}

void Parsing::getCPUID()
{
    /* how get the data */
    QByteArray cpu_id_byte;

    this->data.resize(16);
    for(int i=0; i<16; i++){
        cpu_id_byte[i]=this->data[i];
    }
    this->CPU_ID = cpu_id_byte.toHex();
}

void Parsing::setDatabase()
{
    //VarDataBase->db.addDatabase("QMSQL");
    qDebug()<<"hostname : "<<VarDataBase.hostname;
    qDebug()<<"username : "<<VarDataBase.username;
    qDebug()<<"password : "<<VarDataBase.password;
    qDebug()<<"database : "<<VarDataBase.database;
    qDebug()<<"port     : "<<VarDataBase.port;

    VarDataBase.db.addDatabase("QMSQL");
    VarDataBase.ok = VarDataBase.db.open();

    if (VarDataBase.ok){
        qDebug()<<"Database established";
    } else {
        qDebug()<<"Database not established";
    }



}

void Parsing::startParsing()
{

    /* read from argc argv */
    /* go to conection to mysql */



}

void Parsing::initParsing(int argc, char *argv[])
{


    if (argc==1){

        /* Default mode */
        qDebug()<<"Sento default mode argc == 1 siapa";

        VarDataBase.hostname="localhost";
        VarDataBase.username="root";
        VarDataBase.password="";
        VarDataBase.database="Trumon";
        VarDataBase.port=3306;
        /* set connection */
        qDebug()<<"lol";
        setDatabase();

    } else if(argc==6){

        /* Normal mode */
        qDebug()<<"argc = 6";
        VarDataBase.hostname=argv[1];
        VarDataBase.username=argv[2];
        VarDataBase.password=argv[3];
        VarDataBase.database=argv[4];
        /* For casting char to int*/
        QString port_string=argv[5];
        VarDataBase.port=port_string.toInt();

        setDatabase();

        /* Set connection */
    }
    else
    {
        /*error souldbe present */
        qDebug()<<"argc = "<<argc;

        /* Set connection */
    }

}

