#include "patients.h"
#include "ui_patients.h"

Patients::Patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);

    addpatient = std::make_shared<AddPatiets>();
    connect(ui->Add_P_Button,        &QPushButton::clicked,        this,&Patients::SlotAddClick);
    connect(ui->delete_Button,       &QPushButton::clicked,        this,&Patients::SlotDeleteClick);
    connect(ui->SaveButton,          &QPushButton::clicked,        this,&Patients::SlotSaveClick);
    connect(addpatient.get(),        &AddPatiets::SignalAddPatiens,this,&Patients::AddPerson);
    connect(ui->savelexls_pushButton,&QPushButton::clicked,        this,&Patients::SlotSaveExel);

}

Patients::~Patients()
{
    delete ui;
}

void Patients::GetPat(QByteArray *byte)
{

    QDataStream in(byte,QIODevice::ReadOnly);
    int size ;
    int column = ui->tableWidget->columnCount();
    QString text;
    in>>size>>size;
    int id;


    for(int i = 0 ; i<size;i++)
    {
        ui->tableWidget->insertRow(i);
        in>>text;
        id = text.toInt();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(text));

        int j = 1;
        while(j<column)
        {
            in>>text;

            if(j==4)
            {
                ui->tableWidget->setCellWidget(i,j,new QDateEdit(QDate::fromString(text)));
            }
            else
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(text));
            }
            j++;
        }

    }




}

void Patients::AddPerson( QString LastName ,QString Name,
                                   QString  FatherName,QDate Date, QString Phone,QString Addres,
                                   QString  Pasport,  QString NumberStr,QString Daignosys ,QString NodeText)

{

    int id = 0;
    int row = ui->tableWidget->rowCount();
    for(int i = 0 ;i<row;i++)
    {
      id = std::max(ui->tableWidget->item(i,0)->text().toInt(),id);
    }
    ++id;
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(id)));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(LastName));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(Name));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(FatherName));
    ui->tableWidget->setCellWidget(row, 4 , new QDateEdit(Date));
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(Phone));
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(Addres));
    ui->tableWidget->setItem(row,7,new QTableWidgetItem(Pasport));
    ui->tableWidget->setItem(row,8,new QTableWidgetItem(NumberStr));
    ui->tableWidget->setItem(row,9,new QTableWidgetItem(Daignosys));

}



void Patients::SlotAddClick()
{
    addpatient->show();
}

void Patients::SlotDeleteClick()
{
    if(this->removeId == -1) return;
    int id = ui->tableWidget->item(this->removeId,0)->text().toInt();
    ui->tableWidget->removeRow(this->removeId);

    this->removeId = -1;
}

void Patients::SlotSaveClick()
{
    int row =    ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();
    QString text;
    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<quint64(0)<<4<<row;
    for(int i = 0;i<row;i++)
    {
       for(int j = 0 ; j<column;j++)
       {
           if(j==4)
            {
                 text = QDateEdit(ui->tableWidget->cellWidget(i,j)).text();
                 out<<text;
                 continue;
            }
            text = ui->tableWidget->item(i,j)->text();
            out<<text;
       }
    }

    out.device()->seek(0);
    out<<ba.size();
    emit SignalSavePat(ba);

}

void Patients::SlotSaveExel()
{



    QString url =  QFileDialog::getSaveFileName(this,"open file ", "C\\");
    if(url.isEmpty()) return;

    QXlsx::Document xlsxW;

    int row =    ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();

    QString text;

    for(int i = 0;i<row;i++)
    {
        for(int j = 0 ; j<column-1;j++)
       {
           if(j==4)
           {
                 xlsxW.write(i+1, j+1, QVariant(QDateEdit(ui->tableWidget->cellWidget(i,j)).text()));
                 continue;
           }
            xlsxW.write(i+1, j+1, QVariant(ui->tableWidget->item(i,j)->text()));
        }
    }
    xlsxW.saveAs(url);
}



void Patients::on_tableWidget_clicked(const QModelIndex &index)
{
    this->removeId = index.row();
}

