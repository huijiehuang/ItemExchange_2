//User类的函数
#include "main.h"

User::User(char *owner0, char *address0, char *phoneNumber0, char *email0)
{
    strcpy(owner,owner0);
    strcpy(address,address0);
    strcpy(phoneNumber,phoneNumber0);
    strcpy(email,email0);
    formal = 0;
}

void User::display() const
{
    if(strcmp(owner,"*") != 0)
    {
        cout<<"姓名："<<owner<<endl;
        cout<<"住址："<<address<<" 手机："<<phoneNumber<<" 邮箱："<<email<<endl;
        if (formal)
            cout<<"已注册"<<endl;
        else
            cout<<"未注册"<<endl;
    }
}

bool User::ifSameUser (const char *owner0) const
{
    if (strcmp(owner,owner0) == 0) return 1;
    else return 0;
}

bool User::ifformal()
{
    return formal;
}

void User::formalize()
{
    formal = 1;
}

void User::copyUser(User u)
{
    strcpy(owner,u.owner);
    strcpy(address,u.address);
    strcpy(phoneNumber,u.phoneNumber);
    strcpy(email,u.email);
    formal = u.formal;
}

char* User::copyUserName()
{
    return owner;
}
