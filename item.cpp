//Item类的函数
#include "main.h"

Item::Item(char *name0, char *detail0, char *typeDetaila0, char *typeDetailb0, char *typeDetailc0,
           char *owner0, char *address0, char *phoneNumber0, char *email0, char *type0, char *property10, char *property20, char *property30)
{
    strcpy(name,name0);
    strcpy(detail,detail0);
    strcpy(owner,owner0);
    strcpy(address,address0);
    strcpy(phoneNumber,phoneNumber0);
    strcpy(email,email0);
    strcpy(typeDetaila,typeDetaila0);
    strcpy(typeDetailb,typeDetailb0);
    strcpy(typeDetailc,typeDetailc0);
    strcpy(type,type0);
    strcpy(property1,property10);
    strcpy(property2,property20);
    strcpy(property3,property30);
    formal = 1;
}


void Item::display() const
{
    if(strcmp(name,"*") != 0)
    {
        cout<<"物品名："<<name<<"说明："<<detail<<endl;
        cout<<"所有人："<<owner<<" 地址："<<address<<" 手机号："<<phoneNumber<<" 邮箱："<<email<<endl;
        cout<<"类型："<<type<<endl;
        //只输出有效属性
        if (strcmp(property1,"*") == 1)
            cout<<property1<<":"<<typeDetaila;
        if (strcmp(property2,"*") == 1)
            cout<<" "<<property2<<":"<<typeDetailb;
        if (strcmp(property3,"*") == 1)
            cout<<" "<<property3<<":"<<typeDetailc;
        cout<<endl<<endl;
    }
}

bool Item::ifSameName (char *name0) const
{
    if (strcmp(name,name0) == 0) return 1;
    else return 0;
}

bool Item::ifSameDetail(char *detail0) const
{
    if (strcmp(detail,detail0) == 0) return 1;
    else return 0;
}
