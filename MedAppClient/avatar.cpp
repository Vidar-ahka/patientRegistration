#include "avatar.h"
#include "ui_avatar.h"

Avatar::Avatar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Avatar)
{
    ui->setupUi(this);
    connect(ui->SetAvatar_button,&QPushButton::clicked,this,&Avatar::SlotSetAvatar);
    connect(ui->DeletepushButton,&QPushButton::clicked,this,&Avatar::SlotDeleteAvatar);

}

Avatar::~Avatar()
{
    delete ui;
}

void Avatar::SetAvatar(QImage &Image)
{
    ui->Avatar_label->setPixmap(QPixmap::fromImage(Image));

}

void Avatar::SlotSetAvatar()
{
    QString url =  QFileDialog::getOpenFileName(this,"Select","C:\\");
    if(!url.isEmpty())
    {
         QImage img(url);
         ui->Avatar_label->setPixmap(QPixmap::fromImage(img));


         std::shared_ptr<Message> mes = std::make_shared<Message>(P_SetAvatar);
         QVariant var;
         var.setValue(img);
         mes->Insert(var);
         emit   SignalSend(mes);

  }
}

void Avatar::SlotDeleteAvatar()
{
    ui->Avatar_label->setPixmap(QPixmap(":\\Image\\Images\\Avatar.png"));
    std::shared_ptr<Message> mes = std::make_shared<Message>(P_DelteAvatar);
    emit SignalSend(mes);
}

