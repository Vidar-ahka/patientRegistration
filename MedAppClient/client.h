#ifndef CLIENT_H
#define CLIENT_H
#include<QObject>
#include<mainwindow.h>
#include<login.h>
#include<bytearray.h>
#include"message.h"




class Client:public QObject
{
public:



    Client();
    ~Client();
private:

    int id;

    QTcpSocket  *socket = nullptr;
    Login       *login  = nullptr;
    ByteArray   *byte  = nullptr;

    std::shared_ptr<Users >      users ;
    std::shared_ptr<MainWindow>  MW    ;
    std::shared_ptr<UserList>    List  ;
    std::shared_ptr<Profil>      profil;
    std::shared_ptr<Avatar>      avatar;
    std::shared_ptr<Patients>    pat;

    quint64 sizePackAndId = sizeof(quint64)+sizeof(int);

    void RecvSingIn (QDataStream &in);
    void RecvMessage(std::shared_ptr<MessageInfo> info , ByteArray * byte );
    void requestPatData();
    void requestAllMessage();
    void deleteLogin();
    void GetPatients(ByteArray * byte);



public slots:
    void send(std::shared_ptr<MessageBase>  mes);
    void SlotReadyRead();
    void SlotSendSingIn(QString Login , QString Password);
    void SlotSendSingUp(QString Name, QString Login , QString Password);
    void SlotSendMessage(MessageInfo *MI);
    void SavePat(QByteArray &byte);
    void SlotSetStatusMessage(int id);
    void SlotSetAvatar(QString & url);
    void SlotSetTextData(QString Name , QString Login);
    void SlosDeleteAvatar();
};

#endif // CLIENT_H
