#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    ui->File_Widget->hide();
    ui->Image_widget->hide();
    ui->label->hide();
}

MessageWidget::MessageWidget(MessageInfo *info):MessageWidget()
{
    if(info->getTextNotNull())
    {
        SetText(info->GetText());
    }

    if(!info->GetImageList().isEmpty())
    {

         std::shared_ptr<QHBoxLayout> box = std::make_shared<QHBoxLayout>();
         for(auto &i:info->GetImageList())
         {
             NewMessage(box,i);
         }

         ui->Image_widget->setLayout(box.get());
         ui->Image_widget->show();
         LayoutList.push_back(box);
    }



    if(!info->GetFileList().isEmpty())
    {
          std::shared_ptr<QVBoxLayout> box = std::make_shared<QVBoxLayout>();
          size_t c = 0;
          for(auto &i:info->GetFileList())
          {
              NewMessage(box,i);
          }
          ui->File_Widget->setLayout(box.get());
          ui->File_Widget->show();
          LayoutList.push_back(box);
    }

       ui->widget->setStyleSheet(info->GetColor());


}




MessageWidget::~MessageWidget()
{
    delete ui;

}

void MessageWidget::SetText(QString Text)
{

     size_t i  = 0;
     while(((++i) * 50)<Text.size())
     {
         Text.insert(i*50,'\n');
     }
     ui->label->setText(Text);
     ui->label->show();
}



void MessageWidget::NewMessage(std::shared_ptr<QLayout> lay, QImage &img)
{
    if(img.isNull())return;

    std::shared_ptr<FileMessageWidget> FMW = std::make_shared<FileMessageWidget>(img);
    File_list.push_back(FMW);
    LayoutList.push_back(lay);
    lay->addWidget(FMW.get());
}

void MessageWidget::NewMessage(std::shared_ptr<QLayout> lay, QString &Pair)
{
    if(Pair.isEmpty()) return;

    std::shared_ptr<FileMessageWidget>  FMW  = std::make_shared<FileMessageWidget>(Pair);
    File_list.push_back(FMW);
    LayoutList.push_back(lay);
    lay->addWidget(FMW.get());
}



