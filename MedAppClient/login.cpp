#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
   connect(ui->Sing_in_Button,&QPushButton::clicked,this,&Login::SlotClikcSingIn);
   connect(ui->Sing_up_Button,&QPushButton::clicked,this,&Login::SlotClicKSingUp);
   connect(ui->SignUp_next_button,&QPushButton::clicked,this,&Login::SlotClickSingUpNext);
   connect(ui->Chanche_Button,&QPushButton::clicked,this,&Login::Back);
   ui->Password_lineEdit->setEchoMode(QLineEdit::Password);
   ui->newPassword_lineEdit->setEchoMode(QLineEdit::Password);
   ui->NewPasswordlineEdit_2->setEchoMode(QLineEdit::Password);


}

Login::~Login()
{
    delete ui;
}

void Login::SlotClikcSingIn()
{

  if( ui->Login_lineEdit->text().isEmpty() || ui->Password_lineEdit->text().isEmpty())return;
  std::shared_ptr<Message> mes = std::make_shared<Message>(P_SingIn);
  mes->Insert(ui->Login_lineEdit->text());
  mes->Insert(ui->Password_lineEdit->text());
  emit SignalSend(mes);
}


void Login::SlotClicKSingUp()
{
  ui->stackedWidget->setCurrentIndex(1);
}


void Login::SlotClickSingUpNext()
{


 if(ui->Name_lineEdit->text().isEmpty()) return;

 if(ui->newLogin_lineEdit->text().isEmpty()) return;


 if(ui->newPassword_lineEdit->text().isEmpty()||ui->NewPasswordlineEdit_2->text().isEmpty())return ;
 if(ui->newPassword_lineEdit->text()!=ui->NewPasswordlineEdit_2->text())return;

 std::shared_ptr<Message> mes = std::make_shared<Message>(P_SingUp);
 mes->Insert(ui->Name_lineEdit->text());
 mes->Insert(ui->newLogin_lineEdit->text());
 mes->Insert(ui->newPassword_lineEdit->text());
 emit SignalSend(mes);


 ui->stackedWidget->setCurrentIndex(0);
 ui->Login_lineEdit->clear();
 ui->Password_lineEdit->clear();
 ui->newLogin_lineEdit->clear();
 ui->NewPasswordlineEdit_2->clear();
 ui->newPassword_lineEdit->clear();
 ui->Name_lineEdit->clear();



}

void Login::Back()
{
    ui->stackedWidget->setCurrentIndex(0);
}



