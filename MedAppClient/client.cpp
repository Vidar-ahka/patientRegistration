#include "client.h"

Client::Client()
{


socket = new  QTcpSocket();
socket->connectToHost("127.0.0.1",6666);
login =  new Login();
login->show();
connect(socket,&QTcpSocket::readyRead,this,&Client::SlotReadyRead);
connect(login,&Login::SignalSend,this,     &Client::send);

}
Client::~Client()
{
if(login !=nullptr)delete login;
}

void Client::RecvSingIn(QDataStream &in)
{



    in>>this->id;
    deleteLogin();
    MessageInfo::SetSenderId(this->id);
    qDebug()<<"RecvSing In  ";
    int id;
    QString Name;
    QString Login;
    QByteArray img;
    bool imgnotNull;
    int size;

    in>>size>>Name>>
        Login>>imgnotNull;

    users   = std::make_shared<Users>();
    List    = std::make_shared<UserList>(users);
    avatar  = std::make_shared<Avatar>();
    profil  = std::make_shared<Profil>(Name,Login);
    pat     = std::make_shared<Patients>();
    MW      = std::make_shared<MainWindow>(List,avatar,profil,pat);

    if(imgnotNull)
    {
        QImage as;
        in>>as;  
        avatar->SetAvatar(as);
    }

    while(size>0)
    {
    std::shared_ptr<User> user;
    in>>id>>Name>>imgnotNull;
    if(imgnotNull)
    {
        QImage as;
        in>>as;
        user =  std::make_shared<User>(new Data(id,Name,as));
    }
    else
    {
         user  = std::make_shared<User>(new Data(id,Name));

    }
    List ->InsertUser(user);
    users->InserUser(user);
    connect(user.get(),&User::Click,MW.get(),&MainWindow::SlotClick);
    --size;
    }



    connect(pat.get()   , &Patients::SignalSend,              this,&Client::send);
    connect(MW.get()    , &MainWindow::SignalSend,            this,&Client::send);
    connect(profil.get(), &Profil::SignalSend,                this, Client::send);
    connect(avatar.get(), &Avatar::SignalSend,                this,&Client::send);

    requestPatData();
    requestAllMessage();
    MW->show();

}

void Client::RecvMessage(std::shared_ptr<MessageInfo> info , ByteArray * byte)
{
    info->RecvMessage(byte);
    int id  = info->GetId();
    users->GetUser(id)->RecvMessage(info);
}

void Client::GetPatients(ByteArray *byte)
{
    pat->GetPat(byte);
}



void Client::requestPatData()
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<sizePackAndId<<P_GetPat;
    socket->write(ba);

}

void Client::requestAllMessage()
{
    QByteArray  ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<sizePackAndId<<P_GetAllMessage;
    socket->write(ba);

}

void Client::deleteLogin()
{
    login->hide();
    delete login;
    login = nullptr;
}



void Client::SlotReadyRead()
{


    if(byte==nullptr)
    {
       byte = new ByteArray(socket);
    }
    if(!byte->AddByte(socket)) return;

    int packet = byte->GetPacket();

    if(packet == P_SingIn)
    {
        QDataStream in(byte,QIODevice::ReadOnly);
        RecvSingIn(in);
    }
    else if(packet == P_Message)
    {  
       RecvMessage(std::make_shared<MessageInfo>(), byte);
    }
    else if(packet ==P_GetPat)
    {
        GetPatients(byte);
    }

        delete byte;
        byte = nullptr;

    if(socket->size()>0)
    {
        SlotReadyRead();
    }
}


void Client::send(std::shared_ptr<MessageBase>  mes)
{
    mes->build();

    socket->write(*mes->getbyte().get());
}
