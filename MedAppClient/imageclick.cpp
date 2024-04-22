
#include "imageclick.h"
#include "ui_imageclick.h"

ImageClick::ImageClick(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageClick)
{
    ui->setupUi(this);
}

ImageClick::ImageClick(QImage &Image):ImageClick()
{
       ui->Image_Label->setPixmap(QPixmap::fromImage(Image));
}


ImageClick::~ImageClick()
{
    delete ui;
}

void ImageClick::closeEvent(QCloseEvent *event)
{
        delete this;
}


