#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include<QByteArray>
#include<QDataStream>
#include<QIODevice>
#include<qdebug.h>

class ByteArray :public QByteArray
{
public:
    ByteArray();
    ByteArray(QByteArray Byte);
    ByteArray(ByteArray & byte);
   ByteArray & operator = (ByteArray& byte);
    bool AddByte(QByteArray byte);
    int  GetPacket();
    quint64 GetSize();
    void    SetMessageId( );
    int     GetIdMessage();
private:
    quint64 Size = 0;
    int packet   = 0;


};
#endif // BYTEARRAY_H
