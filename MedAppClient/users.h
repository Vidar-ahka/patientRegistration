#ifndef USERS_H
#define USERS_H
#include<memory>
#include<user.h>
#include<unordered_map>
#include<map>
#include<QLayout>
#include<QList>

class Users
{
public:
    Users();
    void InserUser(std::shared_ptr<User> user);
    void setSizeHint(QSize newSize);
    std::shared_ptr<User> GetUser(int id);
    void find(  std::multimap<size_t, std::shared_ptr<User>> & Map , const  QString TextFind);
    void SetParrentNull(QLayout* layout);



private:
   std::unordered_map<int , std::shared_ptr<User>> users_hash;
   QList<std::shared_ptr<User>> users_list;
};

#endif // USERS_H
