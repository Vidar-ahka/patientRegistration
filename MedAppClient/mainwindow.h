
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<userlist.h>
#include<QFileDialog>
#include<patients.h>
#include<avatar.h>
#include<profil.h>
#include"message.h"





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow( std::shared_ptr<UserList>  list, std::shared_ptr<Avatar>   avatar,  std::shared_ptr<Profil>    profil ,  std::shared_ptr< Patients>   pat);

//    MainWindow(  UserList  * const   list,  Avatar *  const avatar,   Profil *  const profil ,   Patients *  const pat);

    ~MainWindow();
public slots:
      void SlotClick();
private slots:
    void SlotReturnPresed();
    void SlotFileButton();
    void on_pushButton_clicked();
signals:
    void  SignalSend(std::shared_ptr<MessageBase> ms);
private:
    User * CurrentUser = nullptr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
