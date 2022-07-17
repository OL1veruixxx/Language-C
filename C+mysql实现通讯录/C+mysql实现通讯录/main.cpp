#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include <WinSock2.h> /*socketͨ�ţ�ϵͳͷ�ļ�*/
#include <windows.h>
#include <stdio.h>
#define OK     1  
#define ERROR  0  
#define MIX    100  
typedef int Status;
typedef char ElemType;
//��㶨��  
typedef struct telebook    //ͨѶ¼���������    
{
    char name[MIX];        //����
    char telephone[MIX];   //�绰���� 
    char address[MIX];     //��ַ  
    char Email[MIX];      //����        
}telebook;


typedef struct LNode      //������  
{
    telebook data; //���������     
    struct LNode* next;  //���ָ����    
}LNode, * LinkList;



//��ȡ�ı���Ϣ  
void readFile(LinkList& L);

//������ĳ�ʼ��   
Status  InitList_L(LinkList& L);

void Find_Name(LinkList& L); //��������ѯ  

void Find_Num(LinkList& L); //��������ѯ  

Status  CreateFromTail(LinkList& L);     //����β�巨��β������Ԫ��  

//��ʼ���������Ա�L�Ѿ�����  
//�ڵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��  
Status ListInsert_L(LinkList& L);

//�ڵ������Ա�L������Ԫ��֮ǰ����Ԫ��  
Status ListInsert_LName(LinkList& L);
Status Fund_LName(LinkList& L);  //Ѱ�Ҹ�������λ��  

//��ʼ���������Ա�L�Ѿ�����  
//ɾ����i��Ԫ��  
Status ListDelete_L(LinkList& L);

Status ListDelete_LName(LinkList& L);   //ɾ������Ϊ��XXX����ѧ����¼  

void saveFile(LinkList& L);  //����ͨѶ¼���ļ�  

//��ʼ���������Ա�L�Ѿ�����  
//��ӡ������Ԫ��  
void PrintElem(LinkList L);

void List_free(LinkList L);  //��������  

//������ĳ�ʼ��  
Status  InitList_L(LinkList& L)
{
    L = (LNode*)malloc(sizeof(LNode));   //������ռ�   
    if (L == NULL)                       //�ж��Ƿ����㹻���ڴ�ռ�   
        printf("�����ڴ�ռ�ʧ��\n");
    L->next = NULL;                  //��next����ΪNULL,��ʼ����Ϊ0�ĵ�����   
    return OK;
}

void readFile(LinkList& L)          //��ȡ�ļ���Ϣ  
{
    LinkList q, p;
    FILE* fp;
    p = L;
    q = (LNode*)malloc(sizeof(LNode));
    char name[20] = "telebook.txt";    //�½�telebook�ļ�������������Ϣ������ �绰 ����  �������䣩����
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
    printf("                      ����������������\n");
    printf("                                 ��ӭ����ͨѶ¼\n");
    printf("                      ����������������\n\n\n");
    printf("	             1:��ʾ����       |	     2:���ӹ���     \n\n");
    printf("	             3:ɾ������       |	     4:��������     \n\n");
    printf("	             5:��ѯ����       |      6:��������  \n\n");
    printf("	             7:��������       |	     8:��������     \n\n");
    printf("	             0:�˳�����       |	      \n\n");
    printf("--------------------------------------------------------------------------------\n");
}

void tip1()
{
    printf("--------------------------------------------------------------------------------\n");
    printf("	             1:��ʾ����       |	     2:���ӹ���     \n\n");
    printf("	             3:ɾ������       |	     4:��������     \n\n");
    printf("	             5:��ѯ����       |      6:��������  \n\n");
    printf("	             7:��������       |  	 8:��������     \n\n");
    printf("	             0:�˳�����       |	      \n\n");
    printf("--------------------------------------------------------------------------------\n");
}

void Find_Name(LinkList& L) //��������ѯ      
{
    LinkList q, p;
    q = L->next;
    printf("����Ҫ��ѯ��������\n");
    p = (LNode*)malloc(sizeof(LNode));
    scanf("%s", p->data.name);
    while (q != NULL && strcmp(q->data.name, p->data.name) != 0)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("ͨѶ¼��û�����������\n");
    }
    else
    {
        printf("�Ѿ��ҵ�����ϵ��!\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("    ����        �绰����             ��ַ             ����         \n");
        printf("-------------------------------------------------------------------------------\n");
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
    }
}

void Find_Num(LinkList& L) //�������ѯ      
{
    LinkList q, p;
    q = L->next;
    printf("����Ҫ��ѯ�ĺ��룺\n");
    p = (LNode*)malloc(sizeof(LNode));
    scanf("%s", p->data.telephone);
    while (q != NULL && strcmp(q->data.telephone, p->data.telephone) != 0)
    {
        q = q->next;
    }
    if (q == NULL)
    {
        printf("ͨѶ¼��û��������룡\n");
    }
    else
    {
        printf("�Ѿ��ҵ�����ϵ��!\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("    ����        �绰����             ��ַ             ����         \n");
        printf("-------------------------------------------------------------------------------\n");
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
    }
}


Status  CreateFromTail(LinkList& L)     //����β�巨��β������Ԫ��  
{
    LinkList r, s;
    r = L;   //rָ��ʼ�ն�ָ̬������ĵ�ǰ��β  
    while (r->next)
    {//β�巨��ֱ�Ӱ�ָ����λ��β��    
        r = r->next;
    }
    s = (LinkList)malloc(sizeof(LNode));
    printf("��β���������ϵ����ϢΪ��\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    ����        �绰����             ��ַ             ����         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = NULL;
    r->next = s;
    saveFile(L);
    return OK;
}

//��ʼ���������Ա�L�Ѿ�����  
//�ڵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��  
Status ListInsert_L(LinkList& L)
{
    LinkList s, p = L;
    int  j = 1, i;
    printf("����Ҫ�����λ�ã�");
    scanf("%d", &i);
    while (p && j < i)
    {  // Ѱ�ҵ�i�����  
        p = p->next;
        ++j;
    }
    if (!p || j > i) { printf("----�޴�λ�����ʧ��-----\n"); return ERROR; }      // iС��1���ߴ��ڱ�  
    s = (LinkList)malloc(sizeof(LNode));  // �����½��  
    printf("�������ϵ����ϢΪ��\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    ����        �绰����             ��ַ             ����         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = p->next;      // ����L��  
    p->next = s;
    saveFile(L);
    return OK;
} // LinstInsert_L  


Status Fund_LName(LinkList& L)  //Ѱ�Ҹ�������λ��  
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

//�ڵ������Ա�L������Ԫ��֮ǰ����Ԫ��  
Status ListInsert_LName(LinkList& L)
{
    LinkList s, q = L, p = L->next;
    printf("����Ҫ��˭������֮ǰ�����Ϣ��");
    int i = Fund_LName(L);
    int j = 1;
    while (q && j < i - 1)
    {  // Ѱ�ҵ�i-1�����  
        q = q->next;
        ++j;
    }
    if (p == NULL) { printf("----���޴������ʧ��-----\n"); return ERROR; }      // ���û���ҵ�  
    s = (LinkList)malloc(sizeof(LNode));  // �����½��  
    printf("�������ϵ����ϢΪ��\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    ����        �绰����             ��ַ             ����         \n");
    printf("-------------------------------------------------------------------------------\n");
    scanf("%s%s%s%s", s->data.name, s->data.telephone, s->data.address, s->data.Email);
    s->next = q->next;      // ����L��  
    q->next = s;
    saveFile(L);
    return OK;
}

//��ʼ���������Ա�L�Ѿ�����  
//ɾ����i��Ԫ��  
Status ListDelete_L(LinkList& L)
{
    LinkList p = L, q;
    int  j = 1, i;
    printf("����Ҫɾ����λ�ã�");
    scanf("%d", &i);
    while (p->next && j < i)
    {  // Ѱ�ҵ�i����㣬����pָ����ǰ��  
        p = p->next;    ++j;
    }
    if (!(p->next) || j > i) { printf("----���޴���ɾ��ʧ��-----\n"); return ERROR; }  // ɾ��λ�ò�����  
    q = p->next;
    p->next = q->next;           // ɾ�����ͷŽ��    
    free(q);
    printf("----ɾ���ɹ�-----\n");
    saveFile(L);
    return OK;
} // ListDelete_L  

Status ListDelete_LName(LinkList& L)   //ɾ������Ϊ��XXX����ѧ����¼  
{
    LinkList p = L, q;
    printf("����Ҫɾ����ѧ����������");
    int  j = 0, i = Fund_LName(L);
    while (p->next && j < i - 1)
    {  // Ѱ�ҵ�i����㣬����pָ����ǰ��  
        p = p->next;    ++j;
    }
    if (!(p->next) || j > i - 1) { printf("----���޴���ɾ��ʧ��-----\n"); return ERROR; }  // ɾ��λ�ò�����  
    q = p->next;
    p->next = q->next;           // ɾ�����ͷŽ��    
    free(q);
    printf("----ɾ���ɹ�-----\n");
    saveFile(L);
    return OK;
}



//��ʼ���������Ա�L�Ѿ�����  
//��ӡ������Ԫ��  
void PrintElem(LinkList L)
{
    LinkList p = L->next;
    printf("��ǰ����ϢΪ��\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("    ����        �绰����             ��ַ             ����         \n");
    printf("-------------------------------------------------------------------------------\n");
    while (p != NULL)
    {
        printf(" %s        %s          %s             %s                           \n", p->data.name, p->data.telephone, p->data.address, p->data.Email);
        p = p->next;
    }
    printf("\n");
}

void saveFile(LinkList& L)  //����ͨѶ¼���ļ�    
{
    FILE* fp;
    LinkList p;
    p = L;
    if ((fp = fopen("telebook.txt", "wt")) == NULL)   exit(0);   // "wt"��ʽ���ļ�ʱ�����Դ�ļ��������ݣ�׷��              
    if (p == NULL || p->next == NULL) //����Ϊ��      
        printf("���Ĳ���������ȷ������ͨѶ¼��Ϊ�գ�\n");
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
        printf("ͨѶ¼�ѱ��棡\n");
    }
}

void List_free(LinkList L)  //��������  
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
    InitList_L(L);   //��ʼ������
    tip();       //printf
    readFile(L);      //��ȡ�ļ�
    for (;;)
    {
        printf("��ѡ��<1-8>,�˳�<0>:");
        scanf("%d", &n);
        if (n > 8)
            break;

        switch (n)
        {
            /*	���ܣ���ȡ�ļ�����ʾ�������ʾ����*/
        case 1:
        {
            system("cls");    //����  

            PrintElem(L);      //��ʾ�ļ����

            tip1();

        }
        break;

        /*	���ܣ����룬���ӹ���*/

        case 2:
        {
            system("cls");
            printf("-------------------------------------------------------------------------------\n");
            printf(" A-��ĩβ���****B-����ڵ�i��֮ǰ****C-����ڡ�xxx��֮ǰ****\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("��ѡ��>>:");

            fflush(stdin);      /*fflush(stdin)������������뻺������
                                ͨ����Ϊ��ȷ����Ӱ���������ݶ�ȡ��
                                �����ڶ���һ���ַ������������Ҫ��ȡһ���ַ���
                                ��ʱӦ����ִ��fflush(stdin)��*/
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


        /*ɾ������*/
        case 3:
        {  system("cls");//���� 

        printf("-------------------------------------------------------------------------------\n");
        printf("            A-ɾ����i����¼****B-ɾ������Ϊ��xxx������ϵ��********\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("��ѡ��>>:");

        fflush(stdin);
        scanf("%c", &class3);
        if (class3 == 'A' || class3 == 'a')
            ListDelete_L(L);
        if (class3 == 'B' || class3 == 'b')
            ListDelete_LName(L);

        tip1();
        }
        break;



        /*�޸Ĺ���*/
        case 4:
        {
            system("cls");//����  



            tip1();
        }
        break;



        /*    ��ѯ����    */

        case 5:
        {
            system("cls");//����  
            printf("-------------------------------------------------------------------------------\n");
            printf("            A-ͨ������������ϵ��****B-ͨ���绰���������ϵ��********\n");
            printf("-------------------------------------------------------------------------------\n");
            printf("��ѡ��>>:");

            fflush(stdin);
            scanf("%c", &class5);
            if (class5 == 'A' || class5 == 'a')
                Find_Name(L);
            if (class5 == 'B' || class5 == 'b')
                Find_Num(L);

            tip1();
        }
        break;


        //	���ܣ�����
        case 6:
        {		    system("cls");//����  
        printf("-------------------------------------------------------------------------------\n");
        printf("            A-ͨ����������ͨѶ¼****B-ͨ���绰��������ͨѶ¼********\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("��ѡ��>>:");

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
        {	system("cls");//����


        tip1();

        }
        break;

        /*	�˳�  */
        case 0:
        {
            //List_free(L); 

            system("cls");  //���� 
            List_free(L);




        }
        break;
        }
    }
}