#include "parsing.h"

Parsing::Parsing()
{

}

void Parsing::test_parsing()
{
    QString test;
    QByteArray data;

    /* get file form database */




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


