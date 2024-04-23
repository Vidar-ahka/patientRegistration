#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    ui->label->hide();
    data =  nullptr;
}



User::User(Data *data):User()
{


  this->data = data;

  CW =  std::make_shared<ChatWindow>(data->GetName());
  Message  = new MessageInfo(data->GetId());
  ui->Name_Label->setText(data->GetName());
  if(!data->ImageisNull())
  {
      ui->Image_label->setPixmap(QPixmap::fromImage(data->GetImage()));
  }


}

User ::User (User & user)
{
    this->operator =(user.data);
}

User::User (User && user)
{
   this->operator =(user);
}
User& User::operator = (User & user)
{
    CW = std::make_shared<ChatWindow>(*user.CW.get());

    if(user.data == nullptr)
    {
        if(data !=nullptr)
        {
           delete data;
        }
        data = nullptr;
        return *this;
    }
    if(data==nullptr)
    {
        data = new Data();
    }
    data->operator =(*user.data);

    return *this;
}
User& User::operator = (User && user)
{
    CW = std::move(user.CW);
    if(data!=nullptr) delete data;
    data = std::move(user.data);
    return *this;
}



User::~User()
{
    if(Message!=nullptr) delete Message;
    if(data != nullptr)  delete data;
    delete ui;
}

void User::mousePressEvent(QMouseEvent *event)
{

    emit Click();
}


void User::RecvMessage(std::shared_ptr<MessageInfo> info)
{

    if(info->NewMessage())
    {
        ++NewMessageCount;
        ui->label->setText(QString::number(NewMessageCount));

    }
    if(!NewMessageCountisNull())
    {
        ui->label->show();
    }
    CW->AddMessage(std::make_shared<MessageWidget>(info.get()),!NewMessageCountisNull());

}



void User::NullNewMessageCount()
{
    NewMessageCount = 0;
    ui->label->hide();
    ui->label->clear();
}

void User::CreateMessage()
{
    if(Message!=nullptr ) return;
    Message = new MessageInfo(this->data->GetId());
}

void User::DropMessage()
{
    delete Message;
    Message = nullptr;
}

void User::SetSaveText(QString text)
{
    this->SaveTextLineEdit = text;
}

QString User::GetSaveText()
{
    return this->SaveTextLineEdit;
}

bool User::NewMessageCountisNull()
{
    return NewMessageCount == 0;
}




