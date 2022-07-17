#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include <WinSock2.h> /*socket通信，系统头文件*/
#include <windows.h>
#include <stdio.h>
#define OK     1  
#define ERROR  0  
#define MIX    100  
typedef int Status;
typedef char ElemType;
//结点定义  
typedef struct telebook    //通讯录结点数据域    
{
    char name[MIX];        //姓名
    char telephone[MIX];   //电话号码 
    char address[MIX];     //地址  
    char Email[MIX];      //邮箱        
}telebook;


typedef struct LNode      //链表结点  
{
    telebook data; //结点数据域     
    struct LNode* next;  //结点指针域    
}LNode, * LinkList;



//读取文本信息  
void readFile(LinkList& L);

//单链表的初始化   
Status  InitList_L(LinkList& L);

void Find_Name(LinkList& L); //按姓名查询  

void Find_Num(LinkList& L); //按姓名查询  

Status  CreateFromTail(LinkList& L);     //采用尾插法在尾部插入元素  

//初始条件：线性表L已经存在  
//在单链线性表L的第i个元素之前插入元素  
Status ListInsert_L(LinkList& L);

//在单链线性表L的姓名元素之前插入元素  
Status ListInsert_LName(LinkList& L);
Status Fund_LName(LinkList& L);  //寻找该姓名的位置  

//初始条件：线性表L已经存在  
//删除第i个元素  
Status ListDelete_L(LinkList& L);

Status ListDelete_LName(LinkList& L);   //删除姓名为“XXX”的学生记录  

void saveFile(LinkList& L);  //保存通讯录到文件  

//初始条件：线性表L已经存在  
//打印出所有元素  
void PrintElem(LinkList L);

void List_free(LinkList L);  //销毁链表  

//单链表的初始化  
Status  InitList_L(LinkList& L)
{
    L = (LNode*)malloc(sizeof(LNode));   //申请结点空间   
    if (L == NULL)                       //判断是否有足够的内存空间   
        printf("申请内存空间失败\n");
    L->next = NULL;                  //将next设置为NULL,初始长度为0的单链表   
    return OK;
}

void readFile(LinkList& L)          //读取文件信息  
{
    LinkList q, p;
    FILE* fp;
    p = L;
    q = (LNode*)malloc(sizeof(LNode));
    char name[20] = "telebook.txt";    //新建telebook文件，按行输入信息（姓名 电话 日期  电子邮箱）即可
    if ((fp = fopen(name, "r")) == NULL)
    {
        printf("error\n");
        exit(0);
    }
    while (p->next != NULL)
    {
        p = p->next;
    }
    while (fscanf(fp, "%s%s%s%s\n", q->data.name, q->data.telephone, q->data.address, q->data.Email) != EOF)
    {
        q->next = NULL;
        p->next = q;
        p = q;
        q = (LNode*)malloc(sizeof(LNode));
    }
    fclose(fp);
}
void tip()
{
    printf("                      ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
    printf("                                 欢迎进入通讯录\n");
    printf("                      ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n");
    printf("	             1:显示功能       |	     2:增加功能     \n\n");
    printf("	             3:删除功能       |	     4:待定功能     \n\n");
    printf("	             5:查询功能       |      6:待定功能  \n\n");
    printf("	             7:待定功能       |	     8:待定功能     \n\n");
    printf("	             0:退出功能       |	      \n\n");
    printf("--------------------------------------------------------------------------------\n");
}

void tip1()
{
    printf("--------------------------------------------------------------------------------\n");
    printf("	             1:显示功能       |	     2:增加功能     \n\n");
    printf("	             3:删除功能       |	     4:待定功能     \n\n");
    printf("	             5:查询功能       |      6:待定功能  \n\n");
    printf("	             7:待定功能       |  	 8:待定功能     \n\n");
    printf("	             0:退出功能       |	      \n\n");
    printf("--------------------------------------------------------------------------------\n");
}

void Find_Name(LinkList& L) //按姓名查询      
{
    LinkList q, p;
    q = L->next;
    printf("输入要查询的姓名：\n");
    p = (LNode*)malloc(sizeof(LNode));
    scanf("%s", p->data.name);
    while (q != NULL && strcmp(q->data.name, p->data.name) != 0)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("通讯录中没有这个姓名！\n");
    }
    else
    {
        printf("已经找到此联系人!\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("    姓名        电话号码             地址             邮箱         \n");
        printf("-------------------------------------------------------------------------------\n");
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
    }
}

void Find_Num(LinkList& L) //按号码查询      
{
    LinkList q, p;
    q = L->next;
    printf("输入要查询的号码：\n");
    p = (LNode*)malloc(sizeof(LNode));
    scanf("%s", p->data.telephone);
    while (q != NULL && strcmp(q->data.telephone, p->data.telephone) != 0)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("通讯录中没有这个号码！\n");
    }
    else
    {
        printf("已经找到此联系人!\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("    姓名        电话号码             地址             邮箱         \n");
        printf("-------------------------------------------------------------------------------\n");
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
    }
}


Status  CreateFromTail(LinkList& L)     //采用尾插法在尾部插入元素  
{
    LinkList r, s;
    r = L;   //r指针始终动态指向链表的当前表尾  
    while (r->next)
    {//尾插法，直接把指针移位到尾部    
        r = r->next;
    }
    s = (LinkList)malloc(sizeof(LNode));
    printf("在尾部插入的联系人信息为：\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    姓名        电话号码             地址             邮箱         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = NULL;
    r->next = s;
    saveFile(L);
    return OK;
}

//初始条件：线性表L已经存在  
//在单链线性表L的第i个元素之前插入元素  
Status ListInsert_L(LinkList& L)
{
    LinkList s, p = L;
    int  j = 1, i;
    printf("输入要插入的位置：");
    scanf("%d", &i);
    while (p && j < i)
    {  // 寻找第i个结点  
        p = p->next;
        ++j;
    }
    if (!p || j > i) { printf("----无此位置添加失败-----\n"); return ERROR; }      // i小于1或者大于表长  
    s = (LinkList)malloc(sizeof(LNode));  // 生成新结点  
    printf("插入的联系人信息为：\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    姓名        电话号码             地址             邮箱         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = p->next;      // 插入L中  
    p->next = s;
    saveFile(L);
    return OK;
} // LinstInsert_L  


Status Fund_LName(LinkList& L)  //寻找该姓名的位置  
{
    LinkList s, p = L->next;
    int  i = 0;
    s = (LNode*)malloc(sizeof(LNode));
    scanf("%s", s->data.name);
    while (p != NULL && strcmp(p->data.name, s->data.name) != 0)
    {
        p = p->next;
        ++i;
    }
    return i + 1;
}

//在单链线性表L的姓名元素之前插入元素  
Status ListInsert_LName(LinkList& L)
{
    LinkList s, q = L, p = L->next;
    printf("输入要在谁的姓名之前添加信息：");
    int i = Fund_LName(L);
    int j = 1;
    while (q && j < i - 1)
    {  // 寻找第i-1个结点  
        q = q->next;
        ++j;
    }
    if (p == NULL) { printf("----查无此人添加失败-----\n"); return ERROR; }      // 如果没有找到  
    s = (LinkList)malloc(sizeof(LNode));  // 生成新结点  
    printf("插入的联系人信息为：\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    姓名        电话号码             地址             邮箱         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = q->next;      // 插入L中  
    q->next = s;
    saveFile(L);
    return OK;
}

//初始条件：线性表L已经存在  
//删除第i个元素  
Status ListDelete_L(LinkList& L)
{
    LinkList p = L, q;
    int  j = 1, i;
    printf("输入要删除的位置：");
    scanf("%d", &i);
    while (p->next && j < i)
    {  // 寻找第i个结点，并令p指向其前趋  
        p = p->next;    ++j;
    }
    if (!(p->next) || j > i) { printf("----查无此人删除失败-----\n"); return ERROR; }  // 删除位置不合理  
    q = p->next;
    p->next = q->next;           // 删除并释放结点    
    free(q);
    printf("----删除成功-----\n");
    saveFile(L);
    return OK;
} // ListDelete_L  

Status ListDelete_LName(LinkList& L)   //删除姓名为“XXX”的学生记录  
{
    LinkList p = L, q;
    printf("输入要删除的学生的姓名：");
    int  j = 0, i = Fund_LName(L);
    while (p->next && j < i - 1)
    {  // 寻找第i个结点，并令p指向其前趋  
        p = p->next;    ++j;
    }
    if (!(p->next) || j > i - 1) { printf("----查无此人删除失败-----\n"); return ERROR; }  // 删除位置不合理  
    q = p->next;
    p->next = q->next;           // 删除并释放结点    
    free(q);
    printf("----删除成功-----\n");
    saveFile(L);
    return OK;
}



//初始条件：线性表L已经存在  
//打印出所有元素  
void PrintElem(LinkList L)
{
    LinkList p = L->next;
    printf("当前的信息为：\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    姓名        电话号码             地址             邮箱         \n");
    printf("-------------------------------------------------------------------------------\n");
    while (p != NULL)
    {
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
        p = p->next;
    }
    printf("\n");
}

void saveFile(LinkList& L)  //保存通讯录到文件    
{
    FILE* fp;
    LinkList p;
    p = L;
    if ((fp = fopen("telebook.txt", "wt")) == NULL)   exit(0);   // "wt"方式打开文件时，如果源文件中有内容，追加              
    if (p == NULL || p->next == NULL) //链表为空      
        printf("您的操作有误，请确保您的通讯录不为空！\n");
    else
    {
        p = p->next;
        while (p != NULL)
        {
            fprintf(fp, "%s       %s\t      %s          %s", p->data.name, p->data.telephone, p->data.address, p->data.Email);
            fprintf(fp, "\n");
            p = p->next;
        }
        fclose(fp);
        printf("通讯录已保存！\n");
    }
}

void List_free(LinkList L)  //销毁链表  
{
    LinkList p;
    while (L != NULL)
    {
        p = L;
        L = L->next;
        free(p);
        exit(0);
        //system("exit");
    }
}



void main()
{
    int n;
    char class2, class3, class5, class6;
    LinkList L;
    InitList_L(L);   //初始化链表
    tip();       //printf
    readFile(L);      //读取文件
    for (;;)
    {
        printf("请选择<1-8>,退出<0>:");
        scanf("%d", &n);
        if (n > 8)
            break;

        switch (n)
        {
            /*	功能：读取文件并显示结果，显示功能*/
        case 1:
        {
            system("cls");    //清屏  

            PrintElem(L);      //显示文件结果

            tip1();

        }
        break;

        /*	功能：插入，增加功能*/

        case 2:
        {
            system("cls");
            printf("-------------------------------------------------------------------------------\n");
            printf(" A-在末尾添加****B-添加在第i条之前****C-添加在“xxx”之前****\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("请选择>>:");

            fflush(stdin);      /*fflush(stdin)是用来清空输入缓冲区，
                                通常是为了确保不影响后面的数据读取，
                                例如在读完一个字符串后紧接着又要读取一个字符，
                                此时应该先执行fflush(stdin)。*/
            scanf("%c", &class2);
            if (class2 == 'A' || class2 == 'a')
                CreateFromTail(L);
            if (class2 == 'B' || class2 == 'b')
                ListInsert_L(L);
            if (class2 == 'C' || class2 == 'c')
                ListInsert_LName(L);

            tip1();
        }
        break;


        /*删除功能*/
        case 3:
        {  system("cls");//清屏 

        printf("-------------------------------------------------------------------------------\n");
        printf("            A-删除第i条记录****B-删除姓名为“xxx”的联系人********\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("请选择>>:");

        fflush(stdin);
        scanf("%c", &class3);
        if (class3 == 'A' || class3 == 'a')
            ListDelete_L(L);
        if (class3 == 'B' || class3 == 'b')
            ListDelete_LName(L);

        tip1();
        }
        break;



        /*修改功能*/
        case 4:
        {
            system("cls");//清屏  



            tip1();
        }
        break;



        /*    查询功能    */

        case 5:
        {
            system("cls");//清屏  
            printf("-------------------------------------------------------------------------------\n");
            printf("            A-通过姓名查找联系人****B-通过电话号码查找联系人********\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("请选择>>:");

            fflush(stdin);
            scanf("%c", &class5);
            if (class5 == 'A' || class5 == 'a')
                Find_Name(L);
            if (class5 == 'B' || class5 == 'b')
                Find_Num(L);

            tip1();
        }
        break;


        //	功能：排序
        case 6:
        {		    system("cls");//清屏  
        printf("-------------------------------------------------------------------------------\n");
        printf("            A-通过姓名排序通讯录****B-通过电话号码排序通讯录********\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("请选择>>:");

        fflush(stdin);
        scanf("%c", &class6);
        if (class6 == 'A' || class6 == 'a')
            //  
            if (class6 == 'B' || class6 == 'b')
                //  	

                tip1();
        }
        break;



        case 8:
        {	system("cls");//清屏


        tip1();

        }
        break;

        /*	退出  */
        case 0:
        {
            //List_free(L); 

            system("cls");  //清屏 
            List_free(L);




        }
        break;
        }
    }
}