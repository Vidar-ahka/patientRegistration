#include "database.h"




DataBase::DataBase()
{



    DB  = QSqlDatabase::addDatabase("QPSQL");
    DB.setDatabaseName("Telegram");
    DB.setHostName("localhost");
    DB.setUserName("postgres");
    DB.setPassword("zsax1234");
    DB.setPort(5432);


    if(!DB.open())
    {
        qDebug()<<"don't open";
        return;
    }

    QSqlQuery  SQ(DB);

     if(SQ.exec("CREATE TABLE Users(Id_user SERIAL  PRIMARY KEY   ,Name_user VARCHAR(30) , Login_user VARCHAR(30) , Passw_user VARCHAR(30) ,  Ava BYTEA);" ))
         qDebug()<<" Created  Table Users";

     else qDebug()<< " Table Users was created or an error occudrred";

     if(SQ.exec("CREATE TABLE Pat(Id_user INT  , Byte BYTEA);" ));
        qDebug()<<" Created  Table Pat";

     if(!SQ.exec("CREATE TABLE Chats(IdSender INT,IdRecv INT, Size INT , look BOOL,Byte BYTEA);"))qDebug()<<"  NO Create Table Chats";

     else qDebug()<<"Table Chats was create or  an error occuderred";
}

DataBase::DataBase(DataBase & db)
{
    this->DB = db.DB;

}
DataBase::~DataBase()
{

}
bool DataBase::GetUserName(QByteArray &ba)
{


}

void DataBase::AddUser(User* user)
{
    QDataStream in(user->GetByteArray());
    QString Name;
    QString Login;
    QString Password;
    in>>Name>>Login>>Password;


    if(Name.isEmpty()||Login.isEmpty()||Password.isEmpty()) return;
    QSqlQuery QDB(DB);


    QDB.prepare("INSERT INTO Users(Name_user,Login_user,Passw_user) VALUES(:Name,:Login,:Passw);");
    QDB.bindValue(":Name",Name);
    QDB.bindValue(":Login",Login);
    QDB.bindValue(":Passw",Password);
    if(!QDB.exec())return;
    int id = 0;
    QDB.prepare("SELECT Id_user FROM Users WHERE Login_user = :Login  ; ");
    QDB.bindValue(":Login",Login);
    if(QDB.exec()){
    while(QDB.next())
    {
        id = QDB.value(0).toInt();
    }
}

    QDB.prepare("INSERT INTO Pat(Id_user, Byte) VALUES(:Id_user, :Byte) ;");
    QDB.bindValue(":Id_user",id);
    QDB.bindValue(":Byte","");
    QDB.exec();
    return ;


}

bool DataBase::SearchUser(User * user )
{
   QDataStream in(user->GetByteArray());
   QString Login;
   QString Password;
   in>>Login>>Password;

   if(Login.isEmpty()||Password.isEmpty()) return false;

   QSqlQuery  QDB(DB);
   QDB.prepare("SELECT  Id_user  FROM Users WHERE Login_user = :Login AND Passw_user = :Passw ;");
   QDB.bindValue(":Login",Login);
   QDB.bindValue(":Passw",Password);


   if(!QDB.exec())
   {
       return false;
   }
   int id = -1;
   while(QDB.next())
   {
       id = QDB.value(0).toInt();
   };
   user->Setid(id);
   return id>-1;

}

bool DataBase::SingIn(int id, QByteArray &ba)
{



    QDataStream out(&ba,QIODevice::WriteOnly);
    QSqlQuery SQ(DB);

    SQ.prepare("SELECT   Name_user  , Login_user, Ava FROM Users  WHERE Id_user = :id ;");
    SQ.bindValue(":id",id);
    if(!SQ.exec())return false;

    out<<quint64(0)<<1<<id<<0;

    while(SQ.next())
    {
        out<<SQ.value(0).toString()<<SQ.value(1).toString()<<SQ.value(2).toBool();
        if(SQ.value(2).toBool())
        {
            ba.append(SQ.value(2).toByteArray());
            out.device()->seek(ba.size());
        }
    }



    SQ.prepare("SELECT Id_user , Name_user , Ava FROM Users ;");
    if(!SQ.exec())return false;

    int size = 0;
    while(SQ.next())
    {
        out<<SQ.value(0).toInt()<<SQ.value(1).toString()<<SQ.value(2).toBool();

        if(SQ.value(2).toBool())
        {

            ba.append(SQ.value(2).toByteArray());
            out.device()->seek(ba.size());
            //out<<SQ.value(2).toByteArray();
        }
        size++;
    }
    if(size != 0 )
    {
        out.device()->seek(16);
        out<<size;
    }
    out.device()->seek(0);
    out<<ba.size();
    return true;
}
bool DataBase::CreateNewTableChat(QString &str)
{
    QSqlQuery SQ(DB);
    return SQ.exec("CREATE TABLE " + str +" ( look BOOL,Id INT, byte TEXT);");

}



bool DataBase::GetMessage(int id, QByteArray &ba)
{


     QSqlQuery SQ(DB);

     quint64 Size = 0;
     SQ.prepare("SELECT Size FROM Chats WHERE IdSender  = :id OR IdRecv = :id ;");
     SQ.bindValue(":id",id);
     if(!SQ.exec()) return false;

     while(SQ.next())
     {
       Size+=SQ.value(0).toUInt();
     }

     if(Size == 0)
     {
        return false;
     }
     ba.reserve(Size);


     SQ.prepare("SELECT look ,   Byte  FROM Chats WHERE IdSender  = :id OR IdRecv = :id ;");
     SQ.bindValue(":id",id);
     if(!SQ.exec()) return false;


         quint64  SizePrev = 0;
         while(SQ.next())
         {

             ba.append(SQ.value(1).toByteArray());
             if(SQ.value(0).toBool())
             {
                ba[SizePrev+12] = true;
             }

             SizePrev = ba.size();


         }
      return true;
}
bool DataBase::InsertMessage(User *user)
{

    QSqlQuery SQ(DB);



    SQ.prepare("INSERT INTO  Chats( IdSender ,IdRecv , Size , look   ,Byte  ) VALUES(:IdSender, :IdRecv, :Size, :look, :Byte );");
    SQ.bindValue(":IdSender" ,user->Getid());
    SQ.bindValue(":IdRecv"   ,user->GetByteArray().GetIdMessage());
    SQ.bindValue(":Size"     ,user->GetByteArray().size());
    SQ.bindValue(":Byte"     ,user->GetByteArray());
    SQ.bindValue(":look"    ,false);

    return SQ.exec();
}

bool DataBase::SetStatusMessage(User * user)
{
      QDataStream in(&user->GetByteArray(),QIODevice::ReadOnly);
      int id;
      in>>id;

      QSqlQuery SQ(DB);
      SQ.prepare("UPDATE  Chats  SET  look = true WHERE IdSender=:id1 AND IdRecv=:id2;");
      SQ.bindValue(":id1",id);
      SQ.bindValue(":id2",user->Getid());
      return SQ.exec();



}

bool DataBase::AddPatients(User * user)
{
    QSqlQuery SQ(DB);

    SQ.prepare("UPDATE Pat SET  Byte = :byte  WHERE  Id_user = :id");

    SQ.bindValue(":id",user->Getid());

    SQ.bindValue(":byte",user->GetByteArray());


    return SQ.exec();
}

bool DataBase::GetPatients(int id, QByteArray &by)
{
    by.clear();
    QSqlQuery SQ(DB);
    SQ.prepare("SELECT Byte FROM Pat WHERE Id_user = :id ;");
    SQ.bindValue(":id",id);

    if(!SQ.exec())return false;

    QDataStream out(&by,QIODevice::WriteOnly);
    out<<quint64(0)<<5;
    while(SQ.next())
    {

        out<<SQ.value(0).toByteArray();

    }

    if(by.size()-12==0)
    {

        return false;
    }
    out.device()->seek(0);
    out<<by.size();
    return true;
}

bool DataBase::SetAvatarUser(User *user)
{

    QSqlQuery SQ(DB);
    SQ.prepare("UPDATE Users SET Ava = :ava  WHERE Id_user = :id;");
    SQ.bindValue(":id" , user->Getid());
    SQ.bindValue(":ava", user->GetByteArray());
    return SQ.exec();
}

bool DataBase::DeleteAvatarUser(User * user)
{

    QSqlQuery SQ(DB);
    SQ.prepare("UPDATE Users SET Ava = :ava  WHERE Id_user = :id;");
    SQ.bindValue(":id" ,user->Getid());
    SQ.bindValue(":ava","");
    return SQ.exec();

}

bool DataBase::SetData(User *user)
{
    QString Name;
    QString Login;
    QDataStream in(&user->GetByteArray(),QIODevice::ReadOnly);
    in>>Name>>Login;
    QSqlQuery SQ(DB);
    SQ.prepare("UPDATE Users SET Name_user = :Name, Login_user = :Login WHERE Id_user = :id");
    SQ.bindValue(":Name" , Name );
    SQ.bindValue(":Login" , Login);
    SQ.bindValue(":id",user->Getid());

    return SQ.exec();


}
