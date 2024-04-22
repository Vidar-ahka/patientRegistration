#include "filemessagewidget.h"
#include "ui_filemessagewidget.h"


FileMessageWidget::FileMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileMessageWidget)
{
    ui->setupUi(this);
}

FileMessageWidget::FileMessageWidget(QString&Pair):FileMessageWidget()
{


    NameFile = new QLabel;



         int j =  Pair.lastIndexOf('/',Pair.size());
         NameFile->setText(Pair.mid(j+1,Pair.size()));




     ui->Comp_File->addWidget(NameFile);
    ui->file->show();
    this->Url = Pair;


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
    delete NameFile;
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
