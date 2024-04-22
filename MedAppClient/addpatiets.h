#ifndef ADDPATIETS_H
#define ADDPATIETS_H

#include <QWidget>
#include<QDateEdit>


namespace Ui {
class AddPatiets;
}

class AddPatiets : public QWidget
{
    Q_OBJECT


public:
    explicit AddPatiets(QWidget *parent = nullptr);
    AddPatiets(AddPatiets & addpat);
    AddPatiets & operator =(AddPatiets & addpat);
    AddPatiets(AddPatiets && addpat);
    AddPatiets & operator =(AddPatiets && addpat);

    ~AddPatiets();
private slots:
    void SlotClickOk();
    void SlotClickChance();



private:

    Ui::AddPatiets *ui;
signals:
    void SignalAddPatiens(QString LastName ,QString Name,
                          QString  FatherName,QDate Date, QString Phone,QString Addres,
                          QString  Pasport,  QString NumberStr,QString Daignosys ,QString NodeText);
    void SetNode(int id ,QString text);
};

#endif // ADDPATIETS_H
