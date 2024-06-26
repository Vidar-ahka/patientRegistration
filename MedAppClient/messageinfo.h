#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H
#include<QFileInfo>
#include<QString>
#include<QImage>
#include<QList>
#include<QBuffer>
#include"QDir"
#include"QStandardPaths"
#include"message.h"
class  DataFile;

class MessageInfo : public MessageBase
{
public:
    MessageInfo();
    MessageInfo(int id);
    MessageInfo(QByteArray *byte);
    MessageInfo(const MessageInfo &  MW);
    MessageInfo(MessageInfo && MW);

    ~MessageInfo();

    void setbytearray(std::shared_ptr<QByteArray> byte_);
    std::shared_ptr<QByteArray> getbyte();
    void build() ;




    void InsetText  (const QString   &Text);
    void InsertFile (const QString & Url);
    void RecvMessage(QByteArray * const   ba);
    void SendMessage(QByteArray & ba);


    int  GetId();
    QString GetText();
    QString GetColor();
    QList<QImage>&  GetImageList();
    QList<QString>& GetFileList();
    bool getTextNotNull();
    bool NewMessage();
    void Clear();

    static void SetSenderId(const int id);





private:
    void defineColor(bool color);
    void InsertImage(const QString &ImageUrl);
    void RecvImage  (QDataStream &in,int &SizeImage);
    void RecvFile   (QDataStream &in,int &SizeFile);


    static int IdSender;
    static QString downloadPath ;

    int  id;
    QString Color;
    QString Text;

    QList<QImage>   ImageList;
    QList<QString>  FileUrlList;
    bool CheckMessage;
};
class  DataFile
{
    QString Name;
    QString Suffix;
    QString Url;
    quint64 size;
};


#endif // MESSAGEINFO_H
