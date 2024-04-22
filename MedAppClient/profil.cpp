#include "profil.h"
#include "ui_profil.h"

Profil::Profil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Profil)
{
    ui->setupUi(this);
}

Profil::Profil(QString Name, QString Login):Profil()
{
    ui->Name_lineEdit->setText (Name);
    ui->Login_lineEdit->setText(Login);
    this->Name = Name;
    this->Login = Login;
}

Profil::~Profil()
{
    delete ui;
}

void Profil::on_pushButton_clicked()
{

    if(ui->Name_lineEdit->text()!=Name||ui->Login_lineEdit->text()!=Login){
        Name = ui->Name_lineEdit->text();
        Login = ui->Login_lineEdit->text();
        emit SignalSetData(Name ,Login );
    }
}

