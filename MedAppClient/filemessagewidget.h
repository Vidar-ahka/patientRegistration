#ifndef FILEMESSAGEWIDGET_H
#define FILEMESSAGEWIDGET_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include<imageclick.h>
#include<QLabel>
#include<QPixmap>

namespace Ui {
class FileMessageWidget;
}

class FileMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileMessageWidget(QWidget *parent = nullptr);
    FileMessageWidget(QString &Pair);
    FileMessageWidget(QImage  &img);
    ~FileMessageWidget();
    void mousePressEvent(QMouseEvent * event) override;

    QLabel * NameFile  = nullptr;
    QLabel * ImageFile = nullptr;

private:
    Ui::FileMessageWidget *ui;
    QString Url;
};

#endif // FILEMESSAGEWIDGET_H
