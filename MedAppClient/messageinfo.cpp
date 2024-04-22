#include "messageinfo.h"
MessageInfo::MessageInfo()
{
}
MessageInfo::MessageInfo(int id)
{
    this->id = id;
    defineColor(true);
    CheckMessage = true;
}
void MessageInfo::defineColor(bool color)
{
    if(color) Color  = "background-color: rgb(85, 255, 127);" ;
    else  Color = "background-color: rgb(255, 255, 255);";
}
MessageInfo::MessageInfo(QByteArray *byte)
{
       RecvMessage(byte);
}

MessageInfo::~MessageInfo()
{
}
void MessageInfo::InsetText(const QString &Text)
{
    if(Text.isEmpty())return;
    this->Text = Text;
}
void MessageInfo::InsertImage(const QString &ImageUrl)
{
    QImage Img(ImageUrl);

    ImageList.push_back(Img);
}
void MessageInfo::RecvImage(QDataStream &in, int &SizeImage)
{
    QImage img;
    while(SizeImage)
    {
        in>>img;
        ImageList.push_back(img);
        --SizeImage;

    }

}
void MessageInfo::RecvFile(QDataStream &in, int &SizeFile)
{
    QByteArray ba;
    QString name;

    while(SizeFile)
    {
        in>>name>>ba;


        try
        {
            QDir().mkdir(downloadPath);
            name = downloadPath+name;
            QFile file(name);
            if(!file.open(QIODevice::WriteOnly))
            {

               throw name;
            }

            file.write(ba);
            file.close();
            FileUrlList.push_back(name);
        }
        catch(QString  name)
        {
            qDebug()<<"file - "<< name <<"dont open";
        }
        --SizeFile;
    }


}

void MessageInfo::InsertFile(const QString &Url)
{
    QFileInfo FI(Url);

    if(FI.suffix()=="txt")
    {

        FileUrlList.push_back(Url);
        return;
    }

    InsertImage(Url);

}

void MessageInfo::RecvMessage(  QByteArray * const ba)
{
    QDataStream in(ba,QIODevice::ReadOnly);

    int  IdSender2;
    bool TextNotNull ;
    int  SizeImage;
    int  SizeFile;

    in>>CheckMessage>>id>>IdSender2>>TextNotNull>>SizeImage>>SizeFile;

    if(IdSender2 != IdSender)
    {
        defineColor(false);
        this->id = IdSender2;
    }
    else
    {
        defineColor(true);
        CheckMessage = true;
    }
    if(TextNotNull)
    {
        in>>Text;
    }
    if(SizeImage)
    {
        RecvImage(in,SizeImage);
    }
    if(SizeFile)
    {

        RecvFile(in,SizeFile);
   }

}

void MessageInfo::SendMessage(QByteArray &ba)
{
    if(!getTextNotNull()&&ImageList.size()==0&&FileUrlList.size()==0) return;

    int SizeImage = ImageList.size();
    int SizeFile  = FileUrlList.size();
    QDataStream out(&ba,QIODevice::WriteOnly);
    out<<quint64(0)<<3<<false<<this->id<<IdSender<<getTextNotNull()<<SizeImage<<SizeFile;


    if(getTextNotNull())
    {

        out<<Text;
    }
    if(SizeImage > 0)
    {
       for(auto &i:ImageList)
       {
           out<<i;
       }
     }
     if(SizeFile  > 0)   {
         for(auto &i:FileUrlList)
         {

             QFile File(i);

             if(!File.open(QIODevice::ReadOnly)) continue;

             int index = i.lastIndexOf('/',i.size());
             out<<(i.mid(index+1))<<File.readAll();
             File.close();

         }
     }
     out.device()->seek(0);
     out<<ba.size();
}
int MessageInfo::GetId()
{
    return id;
}
QString MessageInfo::GetText()
{
 return  Text;

}
QString MessageInfo::GetColor()
{
    return this->Color;
}
QList<QImage>& MessageInfo::GetImageList()
{
    return ImageList;
}
QList<QString> &MessageInfo::GetFileList()
{
   return FileUrlList;
}
bool MessageInfo::getTextNotNull()
{
    return !Text.isEmpty();
}
bool MessageInfo::NewMessage()
{
    return CheckMessage== false;
}

void MessageInfo::Clear()
{
    Text.clear();
    ImageList.clear();
    FileUrlList.clear();
}
void MessageInfo::SetSenderId(const int id)
{

   IdSender = id;

}
int MessageInfo::IdSender = -1;
QString MessageInfo::downloadPath =  QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)) + "\\MedicalDowload\\";



