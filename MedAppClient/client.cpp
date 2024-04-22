#include "client.h"

Client::Client()
{


socket = new  QTcpSocket();
socket->connectToHost("127.0.0.1",6666);
login =  new Login();
login->show();
connect(socket,&QTcpSocket::readyRead,this,&Client::SlotReadyRead);
connect(login,&Login::SignalSingIn,this,&Client::SlotSendSingIn);
connect(login, &Login::SignalSinUp , this, &Client::SlotSendSingUp);


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

    users =  std::make_shared<Users>();  //new Users();
    List =   std::make_shared<UserList>(users);
    avatar =  std::make_shared<Avatar>();    //new Avatar;
    profil  = std::make_shared<Profil>(Name,Login);    //new Profil(Name,Login);
    pat     = std::make_shared<Patients>();

    MW =      std::make_shared<MainWindow>(List,avatar,profil,pat); //new MainWindow(List,avatar,profil);

    if(imgnotNull)
    {
        in>>img;
        QImage as;
        as.loadFromData(img,"PNG");
        avatar->SetAvatar(as);
    }

    while(size>0)
    {
    std::shared_ptr<User> user;
    in>>id>>Name>>imgnotNull;
    if(imgnotNull)
    {
        in>>img;
        QImage as;
        as.loadFromData(img,"PNG");
        user =  std::make_shared<User>(new Data(id,Name,as));
    }
    else
    {
         user  = std::make_shared<User>(new Data(id,Name));

    }
     qDebug()<<" Size  "<<size;
    List.get() ->InsertUser(user);
    users.get()->InserUser(user);
    qDebug()<<"  Size 2   "<<size;
    connect(user.get(),&User::Click,MW.get(),&MainWindow::SlotClick);

    --size;
    }


     connect(pat.get(),   &Patients::SignalSavePat,           this,&Client::SavePat);
    connect(MW.get(),    &MainWindow::SignalSetStatusMessage,this,&Client::SlotSetStatusMessage);
    connect(avatar.get(),&Avatar::SignalSetAvatar,           this,&Client::SlotSetAvatar);
    connect(avatar.get(),&Avatar::SinglDeleteAvatar,         this,&Client::SlosDeleteAvatar);
    connect(profil.get(),&Profil::SignalSetData,             this, Client::SlotSetTextData);
    connect(MW.get(),    &MainWindow::SignalSendMessage,     this,&Client::SlotSendMessage);
    requestPatData();
    requestAllMessage();
    MW.get()->show();

}

void Client::RecvMessage(std::shared_ptr<MessageInfo> info , ByteArray * byte)
{
    info->RecvMessage(byte);
    int id  = info->GetId();
    users->GetUser(id)->RecvMessage(info);
}

void Client::GetPatients(ByteArray *byte)
{
    pat.get()->GetPat(byte);
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


void Client::SlotSendSingIn(QString Login, QString Password)
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::ReadWrite);
    Packet packet = P_SingIn;
    out<<quint64(0)<<packet<<Login<<Password;
    out.device()->seek(0);

    out<<quint64(ba.size());

    socket->write(ba);


}

void Client::SlotSendSingUp(QString Name, QString Login, QString Password)
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::ReadWrite);
    Packet packet = P_SingUp;
    out<<quint64(0)<<packet<<Name<<Login<<Password;
    out.device()->seek(0);
    out<<ba.size();
    socket->write(ba);

}

void Client::SlotSendMessage(MessageInfo *MI)
{

     QByteArray  option;
     MI->SendMessage(option);
     socket->write(option);
}

void Client::SavePat(QByteArray &byte)
{
    socket->write(byte);
}

void Client::SlotSetStatusMessage(int id)
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<sizePackAndId+4<<P_SetStatusMessage<<id;
    socket->write(ba);
}

void Client::SlotSetAvatar(QString &url)
{


    QByteArray ba;
    QByteArray imgba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    QImage img(url);
    QBuffer bu(&imgba);
    bu.open(QIODevice::WriteOnly);
    out<<quint64(0)<<P_SetAvatar;

    img.save(&bu,"PNG");

    out.device()->seek(0);
    out<<ba.size()+imgba.size();


    socket->write(ba+imgba);
    bu.close();
}

void Client::SlotSetTextData(QString Name , QString Login)
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<quint64(0)<<P_SetData<<Name<<Login;
    out.device()->seek(0);
    out<<ba.size();
    socket->write(ba);
}

void Client::SlosDeleteAvatar()
{
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<sizePackAndId<<P_DelteAvatar;
    socket->write(ba);
}

