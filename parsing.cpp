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
    /* just to show the connection */
    qDebug()<<"hostname : "<<VarDataBase.hostname;
    qDebug()<<"username : "<<VarDataBase.username;
    qDebug()<<"password : "<<VarDataBase.password;
    qDebug()<<"database : "<<VarDataBase.database;
    qDebug()<<"port     : "<<VarDataBase.port;

    VarDataBase.db = QSqlDatabase::addDatabase("QMYSQL");

    /* Setting to database */

    qDebug()<<"setting database";

    VarDataBase.db.setHostName(VarDataBase.hostname);
    VarDataBase.db.setUserName(VarDataBase.username);
    VarDataBase.db.setPassword(VarDataBase.password);
    VarDataBase.db.setDatabaseName(VarDataBase.database);
    VarDataBase.db.setPort(VarDataBase.port);

    /* for test connection */
    VarDataBase.ok = VarDataBase.db.open();



    if (VarDataBase.ok){
        qDebug()<<"Database established";
        startParsing();
    } else {
        qDebug()<<"Database not established";
        // this line should be quit application
    }

}

void Parsing::startParsing()
{
    /* get data from table */
    qInfo()<<"Connected an now to get the database ";

    /* Variable needed */
    QSqlQuery query;
    QString cmd;

    /* Get data */
    cmd = "SELECT * FROM Trumon.NeiraRecv WHERE parsed = 0";

    /* fetch all */

    if(!query.exec(cmd)){
        qInfo()<<"some error";
    }
    else {
        /* get row */
        while(query.next()){
            this->RefNeira = query.value(0).toInt();
            NeiraParsd.idNum = this->RefNeira;

            this->data = query.value(1).toByteArray();
            this->TimeStamp = query.value(2).toDateTime();
            NeiraParsd.FileStamp=this->TimeStamp;

            qInfo()<<"id : "<<this->RefNeira<<" DateTime : "<<this->TimeStamp;


            compareCPUid();
            if(VarDataBase.registeredCPUID){
                qInfo()<<"Registered";

                /* Lets Parse !!!!!!!!!!!!! */
                letsParse();

            }
            else{
                this->CPU_ID;
                qInfo()<<"not registered";
            }
            /* for restoring just like destructor*/
            setDefault();
        }
    }

    VarDataBase.db.close();


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

    } else if(argc==4){
        qDebug()<<"For argc =  "<<argc;
        VarDataBase.hostname="localhost";
        VarDataBase.username=argv[1];
        VarDataBase.password=argv[2];
        VarDataBase.database=argv[3];
        VarDataBase.port=3306;

        setDatabase();


    }
    else if(argc==6){

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

void Parsing::compareCPUid()
{
    /* Query Declare */

    QSqlQuery query;
    QString cmd;
    QString tempCPUID;

    /*Get CPUID*/
    getCPUID();
    cmd = "SELECT * FROM Trumon.NeiraRecvProfile WHERE RegStatus = 1";
    if(!query.exec(cmd)){
        qInfo()<<"Something error";
    } else {

        while(query.next()){
            tempCPUID =  query.value(2).toString();
            if(tempCPUID==this->CPU_ID){
                VarDataBase.registeredCPUID=true;
                qDebug()<<"Wew CPUID : "<<tempCPUID;

                /* get DeviceID */
                NeiraParsd.DeviceId = query.value(1).toString();
                NeiraProf.DeviceId  = query.value(1).toString();

            }
            else{
                qDebug()<<"thisCPUID : "<<this->CPU_ID<<" tempCPUID : "<<tempCPUID;
            }
        }

    }

}

void Parsing::letsParse()
{
    /* get pattern */

    /* Combine Pattern with data */

    /* write to parsed */
    letsWrite();
}

void Parsing::letsWrite()
{
    /* to write in parsed table */
    QSqlQuery query;
    QString cmd;
    cmd = "INSERT INTO Trumon.NeiraParsed (DeviceId, FileStamp, RefNeira) VALUE (:DeviceId, :FileStamp, :RefNeira)";
    query.prepare(cmd);
    query.bindValue(":DeviceId", NeiraParsd.DeviceId);
    query.bindValue(":FileStamp", NeiraParsd.FileStamp);
    query.bindValue(":RefNeira", NeiraParsd.idNum);
    query.exec();


}

void Parsing::setDefault()
{
    VarDataBase.registeredCPUID=false;

}





