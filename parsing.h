#ifndef PARSING_H
#define PARSING_H

#include<QDebug>
#include<QDateTime>
#include "database.h"

class Parsing
{
public:
    Parsing();
    ~Parsing();

    void test_parsing();
    void getCPUID();
    Database *aksesDB;

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
