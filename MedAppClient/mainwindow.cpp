#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::MainWindow(std::shared_ptr<UserList> list, std::shared_ptr<Avatar> avatar, std::shared_ptr<Profil> profil, std::shared_ptr<Patients> pat):MainWindow()
{



    ui->tableLayout->addWidget(pat.get());
    ui->ListLayout->addWidget(list.get());
    ui->DataLayout->addWidget(profil.get());
    ui->AvatarLayout->addWidget(avatar.get());

    connect(ui->File_Button,&QToolButton::clicked,this,&MainWindow::SlotFileButton);
    connect(ui->lineEdit,&QLineEdit::returnPressed,this,&MainWindow::SlotReturnPresed);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotClick()
{
    User *  user = (User*)sender();

   if(!user->CW->isHidden())
   {
      return;
   }

   if(CurrentUser !=  nullptr)
   {
      CurrentUser->CW->hide();
      CurrentUser->SetSaveText(ui->lineEdit->text());
      user->CW->show();
   }

   if(!user->NewMessageCountisNull())
   {
    std::shared_ptr<Message> ms = std::make_shared<Message>(P_SetStatusMessage);
    ms->Insert(user->data->GetId());
    emit SignalSend(ms);
    user->NullNewMessageCount();
   }
    ui->ChatWidget_layout->addWidget(user->CW.get());
    ui->lineEdit->setText(user->GetSaveText());
    CurrentUser = user;
}

void MainWindow::SlotReturnPresed()
{
    if(CurrentUser==nullptr) return;
    QString Text = ui->lineEdit->text();
    if(!Text.isEmpty())
    {
        CurrentUser->CreateMessage();
        CurrentUser->Message->InsetText(Text);
    }

    CurrentUser->CW->AddMessage(std::make_shared<MessageWidget>(CurrentUser->Message),false);

    emit SignalSendMessage(CurrentUser->Message);
    ui->lineEdit->clear();
}




void MainWindow::SlotFileButton()
{
    QString Url =  QFileDialog::getOpenFileName(this,"Select","C:\\");
    if(Url.isEmpty()) return;
    CurrentUser->Message->InsertFile(Url);
}



void MainWindow::on_pushButton_clicked()
{
    SlotReturnPresed();
}

