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
    this->ui = addpat.ui;
}
AddPatiets & AddPatiets:: operator =(AddPatiets& addpat)
{
    this->ui = addpat.ui;
    return *this;
}

AddPatiets::AddPatiets(AddPatiets && addpat)
{
    this->ui = std::move(addpat.ui);
}
AddPatiets& AddPatiets:: operator =(AddPatiets && addpat)
{
    this->ui = std::move(addpat.ui);
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

void AddPatiets::SlotClickChance()
{
    this->hide();

}
