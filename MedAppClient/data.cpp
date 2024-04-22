
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
