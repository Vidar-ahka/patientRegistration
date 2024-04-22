#ifndef PROFIL_H
#define PROFIL_H

#include <QMainWindow>


namespace Ui {
class Profil;
}

class Profil : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profil(QWidget *parent = nullptr);
    explicit Profil(QString  Name , QString Login);
    ~Profil();
signals:
    void SignalSetData(QString Name , QString Login);

private slots:
    void on_pushButton_clicked();

private:
    QString Name;
    QString Login;
    Ui::Profil *ui;
};

#endif // PROFIL_H
