#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <users.h>
#include<QVBoxLayout>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
     UserList(std::shared_ptr<Users>  users);
    ~UserList();
    void InsertUser(std::shared_ptr<User>  user);

public slots:
private slots:
    void SlotTextEdit(const QString &Text);

private:


    std::shared_ptr<Users>  users;
    bool Searchbool = false;
    Ui::UserList *ui;
};

#endif // USERLIST_H
