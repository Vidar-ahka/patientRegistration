#ifndef DATA_H
#define DATA_H

#include<QString>
#include<QImage>

class Data
{
public:
   Data();
   Data(int &id,QString &Name);
   Data(int &id,QString &Name,QImage &Image);

   Data(Data& data);
   Data & operator=(Data & data);
   Data(Data&& data);
   Data & operator=(Data && data);


   ~Data();

  int GetId();
  QString GetName();
  QImage  GetImage();
  bool ImageisNull();

  void SetId   (const int  &id);
  void SetName (const QString &Text);
  void SetImage(const QString &Image);
  void SetImage(const QImage &Image);



private:
  int  id;
  QString Name;
  QString MessageLast;
  QImage Image;



};

#endif // DATA_H
