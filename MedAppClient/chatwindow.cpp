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
    qDebug()<<"add Message Windget";
    ui->verticalLayout->addWidget(MW.get());
    MessageWdigetLsit.push_back(MW);
}



void ChatWindow::SlotArrowButton()
{
   ui->scrollArea->ensureWidgetVisible(EMW.get());
   if(!vis)
   {

       EMW = MessageWdigetLsit[MessageWdigetLsit.size()-1];
       vis = true;
   }
   }


