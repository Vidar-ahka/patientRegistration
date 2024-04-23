#include "ByteArray.h"

ByteArray::ByteArray(QTcpSocket * Byte)
{

    QDataStream in(Byte->read(12));
    in>> Size>>packet;
    Size = Size-12;
    this->reserve(Size);

}


ByteArray::ByteArray(ByteArray & byte)
{
    this->operator =(byte);
}
 ByteArray::ByteArray(ByteArray && byte)
 {
     this->operator =(byte);
 }
ByteArray & ByteArray::operator =(ByteArray &  byte)
{
   this->append(byte);
   this->Size = byte.Size;
   this->packet = byte.packet;
}
ByteArray & ByteArray::operator =(ByteArray && byte)
{
    QByteArray::operator =(byte);
    this->Size = std::move(byte.Size);
    this->packet = std::move(byte.packet);
}


bool ByteArray::AddByte(QTcpSocket * Byte)
{
    quint64 MinSize = Byte->bytesAvailable()>Size ? Size:Byte->bytesAvailable();
    this->append(Byte->read(MinSize));
    Size = Size - MinSize;
    return  Size == 0;
}

int  ByteArray::GetPacket()
{
    return packet;
}

quint64 ByteArray::GetSize()
{

    return   Size;
}

bool ByteArray::IsNewProcess()
{
    return ((this->isEmpty())&&(this->packet==0));
}

void ByteArray::NewProcess()
{
    if(!this->isEmpty()){
    QDataStream in(this,QIODevice::ReadOnly);
    in>> Size>>packet;
    Size = Size-(sizeof(quint64)+sizeof(int));
    this->reserve(Size);
   }
}
void ByteArray::endprocess()
{
    this->packet = 0;
    this->Size   = this->size();
}

