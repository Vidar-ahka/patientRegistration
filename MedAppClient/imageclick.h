#ifndef IMAGECLICK_H
#define IMAGECLICK_H

#include <QWidget>
#include<QString>
#include<QImage>

namespace Ui {
class ImageClick;
}

class ImageClick : public QWidget
{
    Q_OBJECT

public:
    explicit ImageClick(QWidget *parent = nullptr);
    ImageClick(QImage &Image);
    ~ImageClick();
    void closeEvent(QCloseEvent *event);


private:
    Ui::ImageClick *ui;
};

#endif // IMAGECLICK_H
