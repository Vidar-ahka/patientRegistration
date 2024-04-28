#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>
#include<QFileDialog>
#include"message.h"

namespace Ui {
class Avatar;
}

class Avatar : public QWidget
{
    Q_OBJECT

public:
    explicit Avatar(QWidget *parent = nullptr);
    ~Avatar();
    void SetAvatar(QImage & Image);



private slots:
     void SlotSetAvatar();
     void SlotDeleteAvatar();

private:

    Ui::Avatar *ui;
signals:
    void SignalSetAvatar(QString & url);
    void SignalSend(std::shared_ptr<Message> mes);
    void SinglDeleteAvatar();
};

#endif // AVATAR_H
