#include "addpatiets.h"
#include "ui_addpatiets.h"

AddPatiets::AddPatiets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPatiets)
{
    ui->setupUi(this);
    connect(ui->OK_Button,&QPushButton::clicked,this,&AddPatiets::SlotClickOk);
    connect(ui->Chane_Button,&QPushButton::clicked,this,&AddPatiets::SlotClickChance);
}
AddPatiets::AddPatiets(AddPatiets& addpat)
{
    this->operator =(addpat);
}

AddPatiets::AddPatiets(AddPatiets && addpat)
{
    this->operator =(addpat);
}

AddPatiets & AddPatiets:: operator =(AddPatiets& addpat)
{
    copy(addpat);
    return *this;
}
AddPatiets& AddPatiets:: operator =(AddPatiets && addpat)
{

    copy(addpat);

    addpat.ui->LastName_Edit->clear();
    addpat.ui->Name_Edit->  clear();
    addpat.ui->FatherNameEdit->clear();
    addpat.ui->dateEdit->clear();
    addpat.ui->Phone_Edit->clear();
    addpat.ui->Addres_Edit->clear();
    addpat.ui->Pasport_Edit->clear();
    addpat.ui->Med_Edit-> clear();
    addpat.ui->Diagnosys_Edit->clear();
    addpat.ui->Name_Edit->clear();

    return *this;
}


AddPatiets::~AddPatiets()
{
    delete ui;
}

void AddPatiets::SlotClickOk()
{
   emit SignalAddPatiens(ui->LastName_Edit->text(),
                         ui->Name_Edit->text(),
                         ui->FatherNameEdit->text(),
                         ui->dateEdit->date(),
                         ui->Phone_Edit->text(),
                         ui->Addres_Edit->text(),
                         ui->Pasport_Edit->text(),
                         ui->Med_Edit->text(),
                         ui->Diagnosys_Edit->text(),
                         ui->Name_Edit->text());

   this->hide();
    ui->LastName_Edit->clear();
    ui->Name_Edit->clear();
    ui->FatherNameEdit->clear();
    ui->Diagnosys_Edit->clear();
    ui->Nodes_edit->clear();
    ui->Addres_Edit->clear();
    ui->Phone_Edit->clear();
    ui->Pasport_Edit->clear();
    ui->Med_Edit->clear();



}
void AddPatiets::copy(AddPatiets &addpat)
{

    this->ui->LastName_Edit->setText(addpat.ui->LastName_Edit->text());
    this->ui->Name_Edit->setText(addpat.ui->Name_Edit->text());
    this->ui->FatherNameEdit->setText(addpat.ui->FatherNameEdit->text());
    this->ui->dateEdit->setDate(addpat.ui->dateEdit->date());
    this->ui->Phone_Edit->setText(addpat.ui->Phone_Edit->text());
    this->ui->Addres_Edit ->setText(addpat.ui->Addres_Edit->text());
    this->ui->Pasport_Edit->setText( addpat.ui->Pasport_Edit->text());
    this->ui->Med_Edit->setText(addpat.ui->Med_Edit->text());
    this->ui->Diagnosys_Edit->setText(addpat.ui->Diagnosys_Edit->text());
    this->ui->Name_Edit->setText(addpat.ui->Name_Edit->text());

}
void AddPatiets::SlotClickChance()
{
    this->hide();

}
