//实现系统功能的函数
#include "main.h"

User NOWUSER;

void main_menu()
{
   Fl_Window* win = new Fl_Window(300,100, "main_menu");
   win->begin();
   Fl_Button*  b1 = new Fl_Button(10, 20, 200, 30, "log_ad");
   b1->callback(log_ad);
   Fl_Button*  b2 = new Fl_Button(10, 60, 200, 30, "log_user");
   b2->callback(log_user);
   win->end();
   win->show();
}



//实现管理员系统功能的函数
void log_ad(Fl_Widget* w)
{
   Fl_Window* win = new Fl_Window(400,100, "log_ad");
   win->begin();
   Fl_Input*   in  = new Fl_Input(100, 20, 140, 30, "password");
   Fl_Button*  b   = new Fl_Button(300, 20, 60, 30, "enter");
   b->callback(checkPassword,in);
   win->end();
   win->show();
}

void checkPassword(Fl_Widget* w, void* v)
{
   Fl_Input* i=(Fl_Input*)v;
   char password[5] = "1234";
   if (strcmp(i->value(),password) == 0)
     ad_menu();
   else
     popWindow("wrong password");
}

void popWindow(const char* txt)
{
    Fl_Window* win = new Fl_Window(150,60, "");
    win->begin();
    Fl_Box*  b = new Fl_Box(50, 20, 60, 30,txt);
    win->end();
    win->show();
}

void ad_menu()
{
   Fl_Window* win = new Fl_Window(300,200, "ad_menu");
   win->begin();
   Fl_Button*  b1 = new Fl_Button(10, 20, 200, 30, "display type");
   b1->callback(displayAllType);
   Fl_Button*  b2 = new Fl_Button(10, 60, 200, 30, "add type");
   b2->callback(addType);
   Fl_Button*  b3 = new Fl_Button(10, 100, 200, 30, "delete type");
   b3->callback(delType);
   Fl_Button*  b4 = new Fl_Button(10, 140, 200, 30, "admit new users");
   b4->callback(manageUser);
   win->end();
   win->show();
}

void addType(Fl_Widget* w)
{
   char type0[21];
   char property10[21];
   char property20[21];
   char property30[21];
   cout << "请输入类型名:"<<endl;
   cin >> type0;
   cout << "请输入属性名1:"<<endl;
   cin >> property10;
   cout << "请输入属性名2:"<<endl;
   cin >> property20;
   cout << "请输入属性名3:"<<endl;
   cin >> property30;

   Type newType(type0, property10, property20, property30);

   fstream iofile("typeFile.txt");
   Type currentType;

   //添加类型时，先复用被删除类型的空间，若无则添加在文件最后
   int pos = 0;
   iofile.seekg(0);
   iofile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   while (!iofile.eof())
   {
       if(currentType.ifSameType((char*)"*"))
       {
           iofile.seekp(pos * sizeof(Type));
           iofile.write(reinterpret_cast<char *> (&newType), sizeof(Type));
           iofile.close();
           popWindow("add successfully");
           return;
       }
       pos++;
       iofile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   }

   iofile.clear();  //删除读空文件的置错
   iofile.seekp(0,ios::end);
   iofile.write(reinterpret_cast<char *> (&newType), sizeof(Type));
   iofile.close();
   popWindow("add successfully");
}

void delType(Fl_Widget* w)
{
   Type delType;

   char type0[21];
   cout << "请输入类型名:"<<endl;
   cin >> type0;

   fstream iofile("typeFile.txt");
   Type currentType;
   int  pos = 0;

   //删除类型，但不改变其位置
   iofile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   while (!iofile.eof())
   {
       if(currentType.ifSameType(type0))
       {
           iofile.seekp(pos * sizeof(Type));
           iofile.write(reinterpret_cast<char *> (&delType), sizeof(Type));
           iofile.close();
           popWindow("delete successfully");
           return;
       }
       pos++;
       iofile.seekg(pos * sizeof(Type));
       iofile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   }

   iofile.close();
   popWindow("not found");
}

void displayAllType(Fl_Widget* w)
{
   ifstream infile("typeFile.txt");
   Type currentType;

   infile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   while (!infile.eof())
   {
       currentType.display();
       infile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   }

   infile.close();
}

void manageUser(Fl_Widget* w)
{
   Fl_Window* win = new Fl_Window(300,100, "admitUser");
   win->begin();
   Fl_Button*  b1 = new Fl_Button(10, 20, 200, 30, "display all Users");
   b1->callback(displayAllUsers);
   Fl_Button*  b2 = new Fl_Button(10, 60, 200, 30, "manage new Users");
   b2->callback(manageNewUsers);
   win->end();
   win->show();
}

void displayAllUsers(Fl_Widget* w)
{
   ifstream infile("userFile.txt");
   User currentUser;

   infile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!infile.eof())
   {
       currentUser.display();
       infile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   infile.close();
}

void manageNewUsers(Fl_Widget* w)
{
   cout<<"以下成员未注册："<<endl;

   ifstream infile("userFile.txt");
   User currentUser;

   infile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!infile.eof())
   {
       if(currentUser.ifformal() == 0)
          currentUser.display();
       infile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   infile.close();

   Fl_Window* win = new Fl_Window(400,100, "manage user");
   win->begin();
   Fl_Input*   in  = new Fl_Input(100, 20, 140, 30, "user name");
   Fl_Button*  b1  = new Fl_Button(20, 60, 60, 30, "admit");
   Fl_Button*  b2  = new Fl_Button(150, 60, 60, 30, "delete");
   b1->callback(admitUser,in);
   b2->callback(deleteUser,in);
   win->end();
   win->show();

}

void admitUser(Fl_Widget* w, void* v)
{
   Fl_Input* i=(Fl_Input*)v;

   fstream iofile("userFile.txt");
   User currentUser;
   int  pos = 0;


   iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!iofile.eof())
   {
       if(currentUser.ifSameUser(i->value()))
       {
           currentUser.formalize();
           iofile.seekp(pos * sizeof(currentUser));
           iofile.write(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
           iofile.close();
           popWindow("add successfully");
           return;
       }
       pos++;
       iofile.seekg(pos * sizeof(currentUser));
       iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   iofile.close();
   popWindow("not found");
}

void deleteUser(Fl_Widget* w, void* v)
{
   Fl_Input* i=(Fl_Input*)v;

   fstream iofile("userFile.txt");
   User currentUser;
   User delUser;
   int  pos = 0;


   iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!iofile.eof())
   {
       if(currentUser.ifSameUser(i->value()))
       {
           iofile.seekp(pos * sizeof(currentUser));
           iofile.write(reinterpret_cast<char *> (&delUser), sizeof(currentUser));
           iofile.close();
           popWindow("delete successfully");
           return;
       }
       pos++;
       iofile.seekg(pos * sizeof(currentUser));
       iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   iofile.close();
   popWindow("not found");
}




//实现用户系统功能的函数
void log_user(Fl_Widget* w)
{
   Fl_Window* win = new Fl_Window(400,110, "log_ad");
   win->begin();
   Fl_Input*   in  = new Fl_Input(100, 20, 140, 30, "user name");
   Fl_Button*  b1   = new Fl_Button(300, 20, 60, 30, "enter");
   b1->callback(checkUser,in);
   Fl_Button*  b2 = new Fl_Button(10, 70, 140, 30, "sign an account");
   b2->callback(sign);
   win->end();
   win->show();
}

void checkUser(Fl_Widget* w, void* v)
{
   Fl_Input* i=(Fl_Input*)v;

   fstream iofile("userFile.txt");
   User currentUser;
   int  pos = 0;

   iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!iofile.eof())
   {
       if(currentUser.ifSameUser(i->value()))
       {
           iofile.close();
           if ( currentUser.ifformal())
           {
              NOWUSER.copyUser(currentUser);
              user_menu();
           }
           else
             popWindow("not permitted");
           return;
       }
       pos++;
       iofile.seekg(pos * sizeof(currentUser));
       iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   iofile.close();
   popWindow("not found");
}

void sign(Fl_Widget* w)
{
   Fl_Window* win = new Fl_Window(400,200, "sign");
   win->begin();
   Fl_Input*   in1  = new Fl_Input(150, 20, 140, 30, "user name");
   Fl_Input*   in2  = new Fl_Input(150, 60, 140, 30, "address");
   Fl_Input*   in3  = new Fl_Input(150, 100, 140, 30, "telephone number");
   Fl_Input*   in4  = new Fl_Input(150, 140, 140, 30, "email");
   Fl_Button*  b1   = new Fl_Button(320, 20, 60, 30, "sign");
   b1->callback(recordUser);
   win->end();
   win->show();
}

void recordUser(Fl_Widget* w)
{
   Fl_Button* b=(Fl_Button*)w;
   Fl_Input* in1 = (Fl_Input*) b ->parent()->child(0);
   char name0[21];
   strcpy(name0,in1 -> value());
   Fl_Input* in2 = (Fl_Input*) b ->parent()->child(1);
   char address0[40];
   strcpy(address0,in2 -> value());
   Fl_Input* in3 = (Fl_Input*) b ->parent()->child(2);
   char phoneNumber0[12];
   strcpy(phoneNumber0,in3 -> value());
   Fl_Input* in4 = (Fl_Input*) b ->parent()->child(3);
   char email0[40];
   strcpy(email0,in4 -> value());
   User newUser(name0, address0, phoneNumber0, email0);

   fstream iofile("userFile.txt");
   User currentUser;
   //添加用户时，先复用被删除类型的空间，若无则添加在文件最后
   int pos = 0;
   iofile.seekg(0);
   iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   while (!iofile.eof())
   {
       if(currentUser.ifSameUser((char*)"*"))
       {
           iofile.seekp(pos * sizeof(currentUser));
           iofile.write(reinterpret_cast<char *> (&newUser), sizeof(currentUser));
           iofile.close();
           return;
       }
       pos++;
       iofile.read(reinterpret_cast<char *> (&currentUser), sizeof(currentUser));
   }

   iofile.clear();  //删除读空文件的置错
   iofile.seekp(0,ios::end);
   iofile.write(reinterpret_cast<char *> (&newUser), sizeof(currentUser));
   iofile.close();

   popWindow("wait AD's permission");
}

void user_menu()
{
   Fl_Window* win = new Fl_Window(300,200, "user_menu");
   win->begin();
   Fl_Button*  b1 = new Fl_Button(10, 20, 200, 30, "add my item");
   b1->callback(addItem);
   Fl_Button*  b2 = new Fl_Button(10, 60, 200, 30, "delete my item");
   b2->callback(delItem);
   Fl_Button*  b3 = new Fl_Button(10, 100, 200, 30, "display all item");
   b3->callback(displayAllItem);
   Fl_Button*  b4 = new Fl_Button(10, 140, 200, 30, "search item");
   b4->callback(searchItem);
   win->end();
   win->show();
}


void addItem(Fl_Widget* w)
{
   cout<<"请在以下类型中选择一个："<<endl;
   ifstream infile("typeFile.txt");
   Type currentType;
   infile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   while (!infile.eof())
   {
       currentType.display();
       infile.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
   }

   bool exist = 0;
   char type0[21];
   while (exist == 0)
   {
      cout << "请输入类型名:"<<endl;
      cin >> type0;

      ifstream infile2("typeFile.txt");
      infile2.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
      while (!infile2.eof())
      {
         if(currentType.ifSameType(type0))
         {
           exist = 1;
           break;
         }
         infile2.read(reinterpret_cast<char *> (&currentType), sizeof(Type));
      }
      infile2.close();

      if (exist == 0)
        cout<<"类型不存在!"<<endl;
   }

    currentType.display();
    char name[21];
    char detail[40];
    char typeDetaila[21];
    char typeDetailb[21];
    char typeDetailc[21];

   cout << "请输入物品名:"<<endl;
   cin >> name;
   cout << "请输入说明:"<<endl;
   cin >> detail;
   cout << "请输入属性1:"<<endl;
   cin >> typeDetaila;
   cout << "请输入属性2:"<<endl;
   cin >> typeDetailb;
   cout << "请输入属性3:"<<endl;
   cin >> typeDetailc;

   Item newItem(name,detail,typeDetaila,typeDetailb,typeDetailc);
   newItem.copyType(currentType);
   newItem.copyUser(NOWUSER);
   newItem.display();

   Item currentItem;
   fstream iofile("itemFile.txt");
   //添加物品时，先复用被删除物品的空间，若无则添加在文件最后
   int pos = 0;
   iofile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   while (!iofile.eof())
   {
       if(currentItem.ifSameName((char*)"*"))
       {
           iofile.seekp(pos * sizeof(currentItem));
           iofile.write(reinterpret_cast<char *> (&newItem), sizeof(currentItem));
           iofile.close();
           return;
       }
       pos++;
       iofile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   }
   iofile.clear();  //删除读空文件的置错
   iofile.seekp(0,ios::end);
   iofile.write(reinterpret_cast<char *> (&newItem), sizeof(currentItem));
   iofile.close();
   popWindow("add successfully");

}

void displayAllItem(Fl_Widget* w)
{
   ifstream infile("itemFile.txt");
   Item currentItem;

   infile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   while (!infile.eof())
   {
       currentItem.display();
       infile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   }

   infile.close();
}

void delItem(Fl_Widget* w)
{
   char name0[21];
   char owner0[9];
   strcpy(owner0,NOWUSER.copyUserName());
   cout << "请输入物品名:"<<endl;
   cin >> name0;

   fstream iofile("itemFile.txt");
   Item currentItem;
   Item delItem;
   int  pos = 0;

   //删除物品，但不改变其位置
   iofile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   while (!iofile.eof())
   {
       if(currentItem.ifSameName(name0) && currentItem.ifSameUser(owner0))
       {
           iofile.seekp(pos * sizeof(currentItem));
           iofile.write(reinterpret_cast<char *> (&delItem), sizeof(currentItem));
           iofile.close();
           popWindow("delete successfully");
           return;
       }
       pos++;
       iofile.seekg(pos * sizeof(currentItem));
       iofile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
   }

   iofile.close();
   popWindow("not found");
}


void searchItem(Fl_Widget* w){

     char name0[21],type0[21];
     cout << "请输入类型名:"<<endl;
     cin >> type0;
     cout << "请输入物品名或说明:"<<endl;
     cin >> name0;

     ifstream infile("itemFile.txt");
     Item currentItem;
     bool ifExist = 0;

     infile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
     while (!infile.eof())
     {
        if(currentItem.ifSameType(type0) && (currentItem.ifSameName(name0)||currentItem.ifSameDetail(name0)))
        {
            currentItem.display();
            ifExist = 1;
        }
        infile.read(reinterpret_cast<char *> (&currentItem), sizeof(currentItem));
     }
     infile.close();

     if (ifExist == 0)
        popWindow("not found");

}

