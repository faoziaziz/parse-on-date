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
            NeiraProf.dataTrans = query.value(1).toByteArray();
            qDebug()<<"Datanya"<<this->data;
            this->TimeStamp = query.value(2).toDateTime();

            NeiraParsd.FileStamp=this->TimeStamp;

            qInfo()<<"id : "<<this->RefNeira<<" DateTime : "<<this->TimeStamp;


            compareCPUid();
            if(VarDataBase.registeredCPUID ){
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
    getPattern();

    /* Combine Pattern with data */
    letsCombine();

    /* write to parsed */
    letsWrite();
}

void Parsing::letsWrite()
{
    /* to write in parsed table */
    QSqlQuery query;
    QString cmd;
    cmd = "INSERT INTO NeiraParsed (DeviceId, FileStamp, RefNeira, nomerTransaksi, Tanggal, Jam, NomerHP, TotalTrans, POS, Toko, QRString) VALUE (:DeviceId, :FileStamp, :RefNeira, :nomerTransaksi, :Tanggal,  :Jam, :NomerHP, :TotalTrans, :POS, :Toko, :QRString)";
    query.prepare(cmd);
    /* 1 */
    query.bindValue(":DeviceId", NeiraParsd.DeviceId.isEmpty()?"":NeiraParsd.DeviceId);
    query.bindValue(":FileStamp", NeiraParsd.FileStamp);
    query.bindValue(":RefNeira", NeiraParsd.idNum);
    query.bindValue(":nomerTransaksi", NeiraParsd.nomerTransaksi.isEmpty()?"1":NeiraParsd.nomerTransaksi);
    query.bindValue(":Tanggal", NeiraParsd.Tanggal.isEmpty()?"2":NeiraParsd.Tanggal);
    /* 6 */
    query.bindValue(":Jam", NeiraParsd.Jam.isEmpty()?"3":NeiraParsd.Jam);
    query.bindValue(":NomerHP", NeiraParsd.NomerHP.isEmpty()?"4":NeiraParsd.NomerHP);
    query.bindValue(":TotalTrans", NeiraParsd.TotalTrans.isEmpty()?"5":NeiraParsd.TotalTrans);
    query.bindValue(":POS", NeiraParsd.POS.isEmpty()?"6":NeiraParsd.POS);
    query.bindValue(":Toko", NeiraParsd.Toko.isEmpty()?"7":NeiraParsd.Toko);
    /* 11 */

    qInfo()<<"Binding value";
    query.bindValue(":QRString", NeiraParsd.QRString.isEmpty()?"8":NeiraParsd.QRString);
    query.exec();


}

void Parsing::setDefault()
{
    /* The default mode */
    VarDataBase.registeredCPUID=false;

}

void Parsing::getPattern()
{
    QSqlQuery query;
    QString cmd;
    cmd = "SELECT * FROM NeiraRecvProfile WHERE DeviceId = :DeviceId ";
    query.prepare(cmd);
    query.bindValue(":DeviceId", NeiraProf.DeviceId);

    if(!query.exec()){
        qDebug()<<"Query cant exec on getPattern ";
    } else {
        while(query.next()){
            NeiraProf.PatterNoTransaksi=query.value(4).toString();
            NeiraProf.PatternTanggal=query.value(5).toString();
            qDebug()<<"Semoga lancar";
            NeiraProf.PatternJam=query.value(6).toString();
            NeiraProf.PatternHP = query.value(7).toString();
            NeiraProf.PatternTotalTrans=query.value(8).toString();
            NeiraProf.PatternPOS = query.value(9).toString();
            NeiraProf.PatternToko = query.value(10).toString();
            NeiraProf.PatternQRString = query.value(11).toString();
        }
    }
    //NeiraProf.PatternTanggal;

}

void Parsing::letsCombine()
{

    for(int iter=0;iter<NeiraProf.dataTrans.size();iter++){
        if(NeiraProf.dataTrans.at(iter)==0)
            NeiraProf.dataTrans[iter]=' ';
    }

    QRegularExpression RegexNoTrans;
    QRegularExpression RegexTanggal;
    qDebug()<<"patern jam : "<<NeiraProf.PatternJam;
    QRegularExpression RegexJam;
    qDebug()<<"Pattern tanggal "<<NeiraProf.PatternTanggal;
    QRegularExpression RegexHP;
    QRegularExpression RegexTotalTrans;
    QRegularExpression RegexPOS;
    QRegularExpression RegexToko;
    QRegularExpression RegexQRString;

    RegexNoTrans.setPattern(NeiraProf.PatterNoTransaksi);
    RegexTanggal.setPattern(NeiraProf.PatternTanggal);
    RegexJam.setPattern(NeiraProf.PatternJam);
    RegexHP.setPattern(NeiraProf.PatternHP);
    RegexTotalTrans.setPattern(NeiraProf.PatternTotalTrans);
    RegexPOS.setPattern(NeiraProf.PatternPOS);
    RegexToko.setPattern(NeiraProf.PatternToko);
    RegexQRString.setPattern(NeiraProf.PatternQRString);


    NeiraParsd.nomerTransaksi = RegexNoTrans.match(NeiraProf.dataTrans).captured(RegexNoTrans.match(NeiraProf.dataTrans).lastCapturedIndex());

    NeiraParsd.Tanggal = RegexTanggal.match(NeiraProf.dataTrans).captured(RegexTanggal.match(NeiraProf.dataTrans).lastCapturedIndex());
    NeiraParsd.Jam = RegexJam.match(NeiraProf.dataTrans).captured(RegexJam.match(NeiraProf.dataTrans).lastCapturedIndex());
    qDebug()<<"Jamilah :"<<NeiraParsd.Jam;
    qDebug()<<"Regexcx "<<RegexJam.match(NeiraProf.dataTrans);
    NeiraParsd.NomerHP = RegexHP.match(NeiraProf.dataTrans).captured(RegexHP.match(NeiraProf.dataTrans).lastCapturedIndex());
    NeiraParsd.TotalTrans = RegexTotalTrans.match(NeiraProf.dataTrans).captured(RegexTotalTrans.match(NeiraProf.dataTrans).lastCapturedIndex());
    NeiraParsd.POS = RegexPOS.match(NeiraProf.dataTrans).captured(RegexPOS.match(NeiraProf.dataTrans).lastCapturedIndex());
    NeiraParsd.Toko = RegexToko.match(NeiraProf.dataTrans).captured(RegexToko.match(NeiraProf.dataTrans).lastCapturedIndex());
    NeiraParsd.QRString = RegexQRString.match(NeiraProf.dataTrans).captured(RegexQRString.match(NeiraProf.dataTrans).lastCapturedIndex());

}





