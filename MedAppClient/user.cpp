#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    ui->label->hide();
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



User::~User()
{
    if(Message!=nullptr) delete Message;
    delete data;
    delete ui;
}

void User::mousePressEvent(QMouseEvent *event)
{

    emit Click();
}


void User::RecvMessage(std::shared_ptr<MessageInfo> info)
{

    if(info.get()->NewMessage())
    {
        ++NewMessageCount;
        ui->label->setText(QString::number(NewMessageCount));

    }
    if(!NewMessageCountisNull())
    {
        ui->label->show();
    }
    qDebug()<<"RecvMessege";
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




