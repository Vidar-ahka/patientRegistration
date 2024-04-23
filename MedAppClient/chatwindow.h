#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include<messagewidget.h>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT


public:

     explicit ChatWindow(QWidget *parent = nullptr);
     ChatWindow(QString name);
     ChatWindow(ChatWindow & cw);
     ChatWindow(ChatWindow && cw);

     ChatWindow & operator =(ChatWindow &cw);
     ChatWindow & operator =(ChatWindow&&cw);

    ~ChatWindow();

    void AddMessage(std::shared_ptr<MessageWidget> MW, bool newMessage);



private:

    bool vis = true;
    std::shared_ptr<MessageWidget>  EMW;
    QList<std::shared_ptr<MessageWidget>>MessageWidgetList;

    Ui::ChatWindow *ui;
private slots:
    void SlotArrowButton();

};

#endif // CHATWINDOW_H
