#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

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
    void SignalSingIn(QString  Login , QString Password);
    void SignalSinUp(QString Name ,QString  Login , QString Password);


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
