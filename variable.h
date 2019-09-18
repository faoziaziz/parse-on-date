#ifndef VARIABLE_H
#define VARIABLE_H


#include <QDebug>
#include <QDateTime>
#include <QSql>
#include <QSqlDatabase>

class DbVar{
public:
    QSqlDatabase db;
    QString hostname;
    QString username;
    int port;
    QString password;
    QString database;
    bool ok;
    bool registeredCPUID=false;
};

class NeiraProfile {
  public:
    int NoProfile;
    QString DeviceId;
    QString CPU_ID;
    int RegStatus;
    QString PatternTanggal;
    int ParserMode;
    QString PatternJam;
    QString PatternHP;
    QString PatternTotalTrans;
    QString PatternPOS;
    QString PatternToko;
    QString PatterNoTransaksi;
    QString PatternQRString;
};

class NeiraParsed {
  int idNum;
  QString DeviceId;
  QDateTime FileStamp;
  int RefNeira;
  QString Tanggal;
  QString Jam;
  QString NomerHP;
  QString TotalTrans;
  QString POS;
  QString toko;

  QString QRString;

};



#endif // VARIABLE_H
