//Type类的函数
#include "main.h"

Type::Type(char *type0, char *property10, char *property20, char *property30)
{
    strcpy(type,type0);
    strcpy(property1,property10);
    strcpy(property2,property20);
    strcpy(property3,property30);
}

void Type::display() const
{
    if(strcmp(type,"*") != 0)
    {
        cout<<"类型："<<type<<endl;
        cout<<"属性1："<<property1<<" 属性2："<<property2<<" 属性3："<<property3<<endl;
    }
}

bool Type::ifSameType (char *type0) const
{
    if (strcmp(type,type0) == 0) return 1;
    else return 0;
}

void Type::copyType(Type t)
{
    strcpy(type,t.type);
    strcpy(property1,t.property1);
    strcpy(property2,t.property2);
    strcpy(property3,t.property3);
}
