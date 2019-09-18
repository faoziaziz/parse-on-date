#ifndef PARSING_H
#define PARSING_H

#include<QDebug>
#include<QDateTime>
#include "database.h"
#include <QCoreApplication>


class Parsing
{
public:
    Parsing();
    ~Parsing();

    void test_parsing();
    void getCPUID();
    void setDatabase();
    void startParsing();
    void initParsing(int argc, char *argv[]);
    void compareCPUid();
    void letsParse();
    void letsWrite();


    Database *aksesDB;
    DbVar VarDataBase;
    NeiraProfile NeiraProf;
    NeiraParsed NeiraParsd;

private:
    QByteArray data;
    QString CPU_ID;
    QString DeviceId;
    QString Tanggal;
    QString Jam;
    QString NomerHP;
    QString TotalTrans;
    QString POS;
    QString Toko;
    QString QRString;
    int RefNeira;
    QDateTime TimeStamp;
};



#endif // PARSING_H
