#ifndef USER_H
#define USER_H

#include<QTcpSocket>
#include <QString>
#include<bytearray.h>
#include<iostream>



class User:public QTcpSocket
{

public:

    User();
    User(const User & user);
    User & operator =(const User& user);
    ~User();
    void Setid(int id);
    bool isCreateByteArray();
    void CreateByteArray();
    void DropByteArray();
    bool RecvByte();
    int  Getid();
    bool GetOnline();

    ByteArray & GetByteArray();


private:
    int id;
    ByteArray * bytearray;





};

#endif // USER_H

