#ifndef SERVER_H
#define SERVER_H
#include<user.h>
#include<database.h>
#include<memory>
#include<QTcpServer>
class Server:public QTcpServer
{
    enum Packet{P_None = 0 , P_SingIn = 1,P_SingUp = 2 , P_Message = 3,
                P_SavePat = 4,P_GetPat = 5,P_GetAllMessage = 6 ,
                P_SetStatusMessage = 7,P_SetAvatar = 8, P_DelteAvatar = 9
                ,P_SetData = 10};


public:
    Server();
    ~Server();
    QHash<int , User*> Users;
    int i = 0 ;



private slots:
    void incomingConnection(qintptr socketDescrition) ;

   std::unique_ptr<DataBase> db;

public slots:
    void SlotReadyRead();

    void SlotSendMessage(User * user);
    void SlotDeleteConnect();

signals:
    void setId(int);



};

#endif // SERVER_H
