#ifndef PATIENTS_H
#define PATIENTS_H

#include <QMainWindow>
#include<QTableWidget>
#include<QList>
#include<addpatiets.h>
#include<QByteArray>
#include<QIODevice>
#include<QDataStream>
#include<algorithm>
#include <QFileDialog>
#include"message.h"


#include "xlsxdocument.h"
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"
using namespace QXlsx;



namespace Ui {
class Patients;
}

class Patients : public QMainWindow
{
    Q_OBJECT

public:
    explicit Patients(QWidget *parent = nullptr);
    ~Patients();
    void GetPat(QByteArray * byte);
public slots:
    void AddPerson(QString LastName ,QString Name,
                   QString  FatherName,QDate Date, QString Phone,QString Addres,
                   QString  Pasport,  QString NumberStr,QString Daignosys ,QString NodeText);
private slots:
     void SlotAddClick();
     void SlotDeleteClick();
     void SlotSaveClick();
     void SlotSaveExel();
     void on_tableWidget_clicked(const QModelIndex &index);

signals:
     void SignalSavePat(QByteArray &byte);
     void SignalSend(std::shared_ptr<Message> ms );


private:
     int removeId = 0;
     std::shared_ptr<AddPatiets>  addpatient;
     Ui::Patients *ui;



};

#endif // PATIENTS_H
