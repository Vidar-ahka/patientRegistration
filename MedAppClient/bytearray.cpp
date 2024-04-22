#include "ByteArray.h"

ByteArray::ByteArray(QTcpSocket * Byte)
{

    QDataStream in(Byte->read(12));
    in>> Size>>packet;
    Size = Size-12;
    this->reserve(Size);

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

