#ifndef MESSAGE_H
#define MESSAGE_H
#include"memory"
#include"QByteArray"
#include"QMap"
#include"QImage"
#include"QDataStream"
#include"QIODevice"
#include"QVariant"
enum Packet{P_None = 0 , P_SingIn = 1,P_SingUp = 2 , P_Message = 3,
            P_SavePat = 4,P_GetPat = 5,P_GetAllMessage = 6 ,
            P_SetStatusMessage = 7,P_SetAvatar = 8, P_DelteAvatar = 9,
            P_SetData = 10};


class Message
{
public:
    Message();
    Message(Packet packet);
    virtual void setPacket   (Packet packet);
    virtual void Insert(QVariant var);
    virtual void setbytearray(std::shared_ptr<QByteArray> byte_);
    virtual std::shared_ptr<QByteArray> getbyte();
private:
    QList<QVariant> list;
    std::shared_ptr<QByteArray> byte_;
    Packet packet;


};

#endif // MESSAGE_H
