#include "filemessagewidget.h"
#include "ui_filemessagewidget.h"


FileMessageWidget::FileMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMessageWidget)
{
    NameFile = NULL;
    ui->setupUi(this);
}

FileMessageWidget::FileMessageWidget(QString&Pair):FileMessageWidget()
{
    NameFile = std::make_shared<QLabel>();

    int j =  Pair.lastIndexOf('/',Pair.size());

    NameFile->setText(Pair.mid(j+1,Pair.size()));

    ui->Comp_File->addWidget(NameFile.get());
    ui->file->show();
    this->Url = Pair;
}

FileMessageWidget::FileMessageWidget(FileMessageWidget & fmw)
{
    this->operator =(fmw);

}
FileMessageWidget::FileMessageWidget(FileMessageWidget && fmw)
{
    this->operator =(fmw);
}

FileMessageWidget& FileMessageWidget::operator=(FileMessageWidget & fmw)
{
    if(fmw.NameFile==NULL)
    {
        NameFile  = std::make_shared<QLabel>(fmw.NameFile.get());
        ui->Comp_File->addWidget(NameFile.get());
    }
    else
    {
        ui->file->clear();
        ui->file->setPixmap(fmw.ui->file->pixmap());
        ui->file->show();
    }
    Url = fmw.Url;
    return *this;
}
FileMessageWidget& FileMessageWidget::operator=(FileMessageWidget && fmw)
{
    this->NameFile = std::move(fmw.NameFile);
    this->Url = std::move(fmw.Url);
    delete ui;
    this->ui = std::move(fmw.ui);
    return *this;
}





FileMessageWidget::FileMessageWidget(QImage &img):FileMessageWidget()
{

    if(img.isNull())return;

    ui->file->clear();
    QPixmap pix = QPixmap::fromImage(img);
    ui->file->setPixmap(pix);
    ui->file->show();
}


FileMessageWidget::~FileMessageWidget()
{
    delete ui;
}

bool FileMessageWidget::isImage()
{
    return NameFile==NULL;
}

void FileMessageWidget::mousePressEvent(QMouseEvent *event)
{
    if(Url.isEmpty())
    {
        QImage img = ui->file->pixmap().toImage();
        ImageClick * image = new ImageClick(img);
        image->show();

    }
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(Url));

}
