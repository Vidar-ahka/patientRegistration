#include "server.h"

Server::Server()
{
    qDebug()<<"listen to port  6666";
  if(!this->listen(QHostAddress::Any,6666))
  {
      qDebug()<<"listen to port  6666";
      return;
  }
    db = std::make_unique<DataBase>();
}


Server::~Server()
{
 for(auto &i:Users)
 {
    delete i;
 }

}
void Server::incomingConnection(qintptr socketDescrition)
{

    User * socket = new User();
    socket->setSocketDescriptor(socketDescrition);
    connect(socket , &User::readyRead,   this, &Server::SlotReadyRead);
    connect(socket , &User::disconnected,this, &Server::SlotDeleteConnect);
}


void Server::SlotReadyRead()
{


    try{

        User *  user = (User*)sender();
        if(!user->waitForBytesWritten()){
        if(!user->isCreateByteArray())
        {
            user->CreateByteArray();
        }


    if(!user->RecvByte())return;

         qDebug()<<user->GetByteArray().GetPacket();
         switch (user->GetByteArray().GetPacket()) {
         case P_SingIn:
         {
             if(!db->SearchUser(user))
             {
                 break;
             }
             QByteArray ba;
             db->SingIn(user->Getid(),ba);
             Users[user->Getid()] = user;
             user->write(ba);
             break;
         }
         case P_SingUp:
             db->AddUser(user);
             break;
         case P_Message:{
              user->GetByteArray().SetMessageId();
              db->InsertMessage(user);
              int id  =  user->GetByteArray().GetIdMessage();
              if(Users.count(id))
              {
                  Users[id]->write(user->GetByteArray());
              }
            break;
         }
         case P_SavePat:
               db->AddPatients(user);
                break;
         case P_GetPat:{
                QByteArray ba;
                if(!db->GetPatients(user->Getid(),ba))break;
                user->write(ba);
             break;
}
         case P_GetAllMessage:{
             QByteArray ba;
             if(!db->GetMessage(user->Getid(),ba)) break;
             user->write(ba);
             break;
         }
         case P_SetStatusMessage:{
         db->SetStatusMessage(user);
             break;}
         case P_SetAvatar:{
             db->SetAvatarUser(user);
             break;
            }
         case P_DelteAvatar:{
            db->DeleteAvatarUser(user);
             break;}
         case P_SetData:{
             db->SetData(user);
             break;}
         default:
             break;
         }
         }

         user->DropByteArray();
        if(user->size()>0)
        {
             SlotReadyRead();
        }

}
    catch(...)
    {

        qDebug()<<"drop  message ";


    }


}


void Server::SlotDeleteConnect()
{

    User * user = (User*)sender();
    auto it =  Users.find(user->Getid());

    if(it!=Users.end())
    {
        Users.erase(it);
    }

    user->deleteLater();
    delete user;

}


