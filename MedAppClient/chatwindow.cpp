#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    connect(ui->ArrowButton,&QPushButton::clicked,this,&ChatWindow::SlotArrowButton);
}

ChatWindow::ChatWindow(QString name):ChatWindow()
{
      ui->Name->setText(name);
}

ChatWindow::ChatWindow(ChatWindow & cw)
{

}
ChatWindow::ChatWindow(ChatWindow && cw)
{

}

ChatWindow & ChatWindow:: operator =(ChatWindow &cw)
{
    this->vis = cw.vis;
     MessageWidgetList.clear();
    for(auto &it: cw.MessageWidgetList)
    {
        MessageWidgetList.push_back(std::make_shared<MessageWidget>(*it.get()));
    }
    EMW =MessageWidgetList.back();
}
ChatWindow &ChatWindow :: operator =(ChatWindow&&cw)
{
    this->vis = cw.vis;
    MessageWidgetList.clear();
    for(auto it :cw.MessageWidgetList)
    {
        MessageWidgetList.push_back(it);
    }
    this->EMW = std::move(cw.EMW);
    this->ui = std::move(cw.ui);
    return *this;
}

ChatWindow::~ChatWindow()
{
    delete ui;
}


void ChatWindow::AddMessage(std::shared_ptr<MessageWidget>MW,bool newMessage)
{
    if(newMessage&&vis)
    {
        EMW = MW;
        vis = false;
    }
    else if(!newMessage)
    {
        EMW = MW;
    }

    ui->verticalLayout->addWidget(MW.get());
   MessageWidgetList.push_back(MW);
}



void ChatWindow::SlotArrowButton()
{
   ui->scrollArea->ensureWidgetVisible(EMW.get());
   if(!vis)
   {

       EMW =MessageWidgetList.back();
       vis = true;
   }
   }


