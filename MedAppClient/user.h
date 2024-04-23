#ifndef USER_H
#define USER_H

#include <QWidget>
#include<data.h>
#include<chatwindow.h>
#include<messageinfo.h>
#include<messagewidget.h>
#include<Qt>


namespace Ui {
class User;
}


class User : public QWidget
{
    Q_OBJECT

public:
    User(QWidget *parent = nullptr);
    User(Data* data);
    User(User & user);
    User(User && user);
    User & operator = (User & user);
    User & operator = (User && user);
    ~User();

    std::shared_ptr<ChatWindow>  CW ;
    Data  * data;

    void mousePressEvent(QMouseEvent * event) override;
    void RecvMessage(std::shared_ptr<MessageInfo> info);
    void NullNewMessageCount();
    void CreateMessage();
    void DropMessage();
    void SetSaveText(QString text);
    QString GetSaveText();
    bool NewMessageCountisNull();
    MessageInfo * Message;





signals:

    void Click();

private:

    size_t NewMessageCount   =  0;
    QString SaveTextLineEdit = 0;








private:


    Ui::User *ui;
};





#endif // USER_H
