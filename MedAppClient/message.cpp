#include "message.h"


Message::Message(){}
Message::Message(Packet packet)
{
    this->packet = packet;
}
void Message::setPacket   (Packet packet)
{

    this->packet = packet;
}
void Message::Insert(QVariant var)
{
     list.push_back(var);
}
 void Message::setbytearray(std::shared_ptr<QByteArray> byte_)
 {
     this->byte_ = byte_;
 }
 std::shared_ptr<QByteArray> Message::getbyte()
 {
    byte_ = std::make_shared<QByteArray>();
    QDataStream out(byte_.get(),QIODevice::WriteOnly);
    out<<quint64(0) << packet;
    for(auto  &it:list)
    {
       if(QMetaType::Int == it.typeId())
       {
           out <<it.toInt();
       }
       else if(QMetaType::QString == it.typeId())
       {
           out<<it.toString();
       }
       else if(it.canConvert<QImage>())
       {
           QImage img = it.value<QImage>();
           out <<img;
       }
    }

    out.device()->seek(0);
    out<<byte_->size();

    return byte_;
 }
