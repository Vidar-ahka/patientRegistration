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
   MessageWidget(std::shared_ptr<MessageInfo> MI);
   MessageWidget( MessageWidget & mw);
   MessageWidget( MessageWidget && mw);

   MessageWidget & operator =(MessageWidget & mw);
   MessageWidget & operator =(MessageWidget && mw);
   ~MessageWidget();

    void SetText(QString Text);
    int GetId();

private:
    std::shared_ptr<QLayout> file_lay;
    std::shared_ptr<QLayout> image_lay;

    QList<std::shared_ptr<FileMessageWidget>>File_list;
    void  NewMessage(std::shared_ptr<QLayout> lay,std::shared_ptr<FileMessageWidget> FMW);


    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
