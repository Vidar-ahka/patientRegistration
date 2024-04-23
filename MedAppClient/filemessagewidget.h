#ifndef FILEMESSAGEWIDGET_H
#define FILEMESSAGEWIDGET_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include<imageclick.h>
#include<QLabel>
#include"memory"
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

    FileMessageWidget(FileMessageWidget & fmw);
    FileMessageWidget(FileMessageWidget && fmw);

    FileMessageWidget& operator=(FileMessageWidget & fmw);
    FileMessageWidget& operator=(FileMessageWidget && fmw);

    ~FileMessageWidget();
    void mousePressEvent(QMouseEvent * event) override;
    std::shared_ptr<QLabel> NameFile;
    bool isImage();


private:
    Ui::FileMessageWidget *ui;
    QString Url;
};

#endif // FILEMESSAGEWIDGET_H
