#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"memory"
#include"message.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:
    void SlotClikcSingIn();
    void SlotClicKSingUp();
    void SlotClickSingUpNext();
    void Back();

signals:
    void SignalSend(std::shared_ptr<Message> mes);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
