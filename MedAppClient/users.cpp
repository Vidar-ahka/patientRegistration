#include "users.h"

Users::Users()
{
}

void Users::InserUser(std::shared_ptr<User> user)
{
    users_hash[user.get()->data->GetId()] = user;
    users_list.push_back(user);
}

std::shared_ptr<User> Users:: GetUser(int id)
{

    return users_hash[id];
}

void Users::setSizeHint(QSize newSize)
{

}
void Users::find(  std::multimap<size_t, std::shared_ptr<User>> & Map , const  QString TextFind)
{
    if(TextFind.isEmpty())
    {
        return;
    }
    QString text;
    size_t count;
    for(auto &i:users_list)
    {
      text  = i.get()->data->GetName();
      count = 0;
      while(count<text.size()&&text[count]!=' '&&text[count]==TextFind[count])++count;

      if(count!=0)Map.emplace(count,i);
    }




}

void Users::SetParrentNull(QLayout* layout)
{
    if(layout!=nullptr)
      {
        for(auto &i:users_list)
        {
            layout->addWidget(i.get());
        }
        return;
      }

        for(auto &i:users_list)
        {
            i.get()->setParent(nullptr);
        }
}


