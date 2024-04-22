#ifndef ByteArray_H
#define ByteArray_H
#include<QByteArray>
#include<qdebug.h>
#include<QDataStream>
#include<QIODevice>
#include<QBuffer>
#include<QTcpSocket>
class ByteArray:public QByteArray
{
public:


    ByteArray   (QTcpSocket * Byte);
    bool AddByte(QTcpSocket * Byte);
    int   GetPacket();
    quint64 GetSize();
    bool IsNewProcess();
    void NewProcess();
    void endprocess();

private:
    quint64 Size;
    int packet;
};

#endif // ByteArray_H
