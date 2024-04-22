#include "bytearray.h"

ByteArray::ByteArray()
{
    this->clear();
}

ByteArray::ByteArray(QByteArray Byte):ByteArray()
{
    QDataStream in(&Byte,QIODevice::ReadOnly);
    in>> Size >>packet;
    Size  =  Size  - Byte.size();
    this->reserve(Size);
    if(packet==3)this->append(Byte);
}
ByteArray::ByteArray(ByteArray & byte)
{
    this->clear();
    this->reserve(byte.capacity());
    this->append(byte);

}
ByteArray & ByteArray::operator = (ByteArray& byte)
{
    this->clear();
    this->reserve(byte.capacity());
    this->append(byte);
    return *this;
}

bool ByteArray::AddByte(QByteArray byte)
{

    this->append(byte);
    Size  =  Size  - byte.size();
    return  Size  == 0;
}

int ByteArray::GetPacket()
{
    return packet;
}

quint64 ByteArray::GetSize()
{
    return Size;
}

void ByteArray::SetMessageId()
{
    QDataStream in(this , QIODevice::ReadOnly);
    in.device()->seek(sizeof(quint64)+sizeof(int)+1);
    in>>packet;
}

int ByteArray::GetIdMessage()
{
    return packet;
}


