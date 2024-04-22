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
        ui->Avatar_label->setPixmap(url);
        emit SignalSetAvatar(url);
    }
}

void Avatar::SlotDeleteAvatar()
{
    ui->Avatar_label->setPixmap(QPixmap(":\\Image\\Images\\Avatar.png"));
    emit SinglDeleteAvatar();
}

