#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <messageinfo.h>
#include<filemessagewidget.h>
#include<memory>
namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
   explicit MessageWidget(QWidget *parent = nullptr);
   MessageWidget(MessageInfo *info);
   ~MessageWidget();

    void SetText(QString Text);
    int GetId();

private:
    QList<std::shared_ptr<QLayout>>LayoutList;
    QList<std::shared_ptr<FileMessageWidget>>File_list;
    void  NewMessage(std::shared_ptr<QLayout> lay, QImage  &img );
    void  NewMessage(std::shared_ptr<QLayout> lay, QString &Pair);
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
