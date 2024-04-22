#include "userlist.h"
#include "ui_userlist.h"


UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);

    connect(ui->lineEdit,&QLineEdit::textEdited,this,&UserList::SlotTextEdit);
}

UserList::UserList(std::shared_ptr<Users> users):UserList()
{
   this->users = users;
}

UserList::~UserList()
{
    delete ui;
}


void UserList::InsertUser(std::shared_ptr<User> user)
{
    ui->Layout->addWidget(user.get());
}

void UserList::SlotTextEdit(const QString &Text)
{
    if(Text.isEmpty())
    {
        users->SetParrentNull(ui->Layout);
        return;
    }

    users->SetParrentNull(nullptr);
    std::multimap<size_t, std::shared_ptr<User>> Map;
    users->find(Map,Text);
    for(auto i:Map)
    {
       ui->Layout->addWidget(i.second.get());
    }
}



