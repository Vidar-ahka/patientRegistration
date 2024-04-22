#include "user.h"

User::User()
{
    this->id=-1;
    this->bytearray = nullptr;
}
User::User(const User & user)
{
    this->operator =(user);
}

User & User::operator =(const User & user)
{
    this->id = user.id;
    if(user.bytearray==nullptr)
    {
        if(bytearray != nullptr)delete bytearray;
        bytearray = nullptr;
        return *this;
    }
    else if(bytearray==nullptr)
    {
        bytearray = new ByteArray();
    }
    bytearray->operator =(*user.bytearray);

    return *this;
}
User::~User()
{
    if(bytearray!= nullptr) delete bytearray;
}

void User::Setid(int id)
{

    this->id = id;


}

bool User::isCreateByteArray()
{
    return bytearray != nullptr;
}

void User::CreateByteArray()
{
    bytearray = new ByteArray(this->read(12));
}
void User::DropByteArray()
{

    delete bytearray;
    bytearray = nullptr;
}

bool User::RecvByte()
{
     quint64 size = this->bytesAvailable()>bytearray->GetSize()? bytearray->GetSize() : this->bytesAvailable();
    return bytearray->AddByte(this->read(size));
}

int User::Getid()
{
    return this->id;
}
bool User::GetOnline()
{
    return this->id>-1;
}

 ByteArray & User::GetByteArray()
{
    return *bytearray;
}



