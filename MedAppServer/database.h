#ifndef DATABASE_H
#define DATABASE_H
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QFile>
#include<QHash>
#include<QList>
#include<QImage>

#include<user.h>





class DataBase
{
public:

    DataBase();
    DataBase(DataBase & db);
    ~DataBase();
    void  AddUser     (User* user );
    bool  SearchUser  (User* user );
    bool  SingIn(int id,QByteArray &ba);
    bool  GetUserName(QByteArray &ba);
    bool  CreateNewTableChat(QString &str);
    bool  GetMessage(int id, QByteArray & ba);
    bool  InsertMessage(User * user );
    bool  SetStatusMessage(User *user);
    bool  AddPatients(User * user);
    bool  GetPatients(int id,QByteArray & by);
    bool  SetAvatarUser(User * user);
    bool  DeleteAvatarUser(User * user );
    bool  SetData(User * user);





private:
    int SizeRead = sizeof(int )+sizeof(int )+sizeof(int);
    QSqlDatabase DB;




  };

#endif // DATABASE_H
