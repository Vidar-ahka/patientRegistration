
#include "data.h"

Data::Data()
{

}
Data::Data(int &id, QString &Name)
{
     this->id=id;
    this->Name = Name;
}
Data::Data(int &id, QString &Name, QImage  &Image):Data(id,Name)
{
    SetImage(Image);

}
Data::Data(Data& data)
{
    this->operator =(data);
}
Data & Data::operator=(Data & data)
{
    this->id = data.id;
    this->id         = data.id;
    this->Name       = data.Name;
    this->MessageLast= data.MessageLast;
    this->Image      = data.Image;
    return *this;
}
Data::Data(Data&& data)
{
    this->operator =(data);
}
Data & Data::operator=(Data && data)
{
    this->id = std::move(data.id);
    this->id =    std::move(data.id);
    this->Name = std::move(data.Name);
    this->MessageLast = std::move( data.MessageLast);
    this->Image  = std::move(data.Image);
    return *this;
}





Data::~Data(){}

int Data:: GetId(){return this->id;}

QString Data:: GetName()
{
    return this->Name;
}

QImage Data::GetImage()
{
    return this->Image;

}

bool Data::ImageisNull()
{
    return Image.isNull();
}


void Data:: SetId   (const int  &id)
{
    this->id = id;
}

void Data:: SetName (const QString &Text)
{
    this->Name = Text;
}

void Data:: SetImage(const QString &Image){
    QImage img(Image);this->Image = img;
}

void Data::SetImage(const QImage &Image)
{
    this->Image= Image;
}
