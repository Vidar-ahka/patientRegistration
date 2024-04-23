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
    file_lay = NULL;
    image_lay = NULL;
}

MessageWidget::MessageWidget(MessageInfo *info):MessageWidget()
{
    if(info->getTextNotNull())
    {
        SetText(info->GetText());
    }

    if(!info->GetImageList().isEmpty())
    {

         image_lay = std::make_shared<QHBoxLayout>();

         for(auto &i:info->GetImageList())
         {
             NewMessage(image_lay,std::make_shared<FileMessageWidget>(i));
         }

         ui->Image_widget->setLayout(image_lay.get());
         ui->Image_widget->show();

    }



    if(!info->GetFileList().isEmpty())
    {
          file_lay = std::make_shared<QVBoxLayout>();
          for(auto &i:info->GetFileList())
          {
              NewMessage(file_lay,std::make_shared<FileMessageWidget>(i));
          }
          ui->File_Widget->setLayout(file_lay.get());
          ui->File_Widget->show();

    }

       ui->widget->setStyleSheet(info->GetColor());


}


MessageWidget::MessageWidget( MessageWidget & mw)
{
    this->operator =(mw);
}
MessageWidget::MessageWidget( MessageWidget && mw)
{
    this->operator =(mw);
}

MessageWidget & MessageWidget::operator =(MessageWidget & mw)
{
    if(!mw.ui->label->text().isEmpty())
    {
        SetText(mw.ui->label->text());
    }
    if(mw.image_lay == NULL)
    {
        image_lay = std::make_shared<QHBoxLayout>();
    }
    if(mw.file_lay == NULL)
    {
        file_lay = std::make_shared<QVBoxLayout>();
    }

    File_list.clear();

    for(auto &it:mw.File_list)
    {
        std::shared_ptr<FileMessageWidget> ptr =
                std::make_shared<FileMessageWidget>(*it.get());
       if(it->isImage())
       {
          image_lay->addWidget(ptr.get());

       }
       else
       {
           file_lay->addWidget(ptr.get());
       }
    }
    return *this;
}
MessageWidget & MessageWidget::operator =(MessageWidget && mw)
{
    File_list = mw.File_list;
    mw.File_list.clear();

    file_lay = std::move(mw.file_lay);
    image_lay = std::move(mw.image_lay);

    ui = std::move(mw.ui);
    return *this;
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


void MessageWidget:: NewMessage(std::shared_ptr<QLayout> lay
                                ,std::shared_ptr<FileMessageWidget> FMW)
{
    File_list.push_back(FMW);
    lay->addWidget(FMW.get());
}





