#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define size 50

int count=0;

struct card
{
	char name[10];
	char ID[10];
	char password[20];
	char idcard[5];	//���֤��  Ϊ�����ʾ���ú�4λ��ʾ 
	double remain;	//��� 
	int state;		//0��ʾ������1��ʾ���� 
} Card[size];
//={
//	{"��XX","B18111601","888888","0123",95,1}, 
//	{"��XX","B18111602","888888","1234",83,0},
//	{"��XX","B18111603","888888","2345",52,0},
//	{"��XX","B18111604","888888","3456",46,0},
//	{"��XX","B18111605","888888","4567",71,0} 
//};

struct adr
{
	char ID[10];
	char password[20];
} Adr={"123456","123456"};

struct book
{
	char when[20];
	char bookname[20];
	char deadline[20];
};

struct record			 
{
	char ID[10];
	char date[20];		//�������� 
	char start_time[20];//��ʼʱ�� 
	int duration;		//��������ʱ�� 
	char place[20];		//�����ص�
	struct book Book;
};
//Record[10]={
//	{"B18111601","2019.01.01","20:00:00",60,"T9����","2019.04.01","����¥�Ρ�","2019.05.01"},
//	{"B18111601","2019.01.03","19:00:00",90,"T8����","2019.04.01","��˫�Ǽǡ�","2019.05.01"},
//	{"B18111602","2019.01.01","20:00:00",60,"T9����","2019.04.01","���������硷","2019.05.01"},
//	{"B18111602","2019.02.01","09:00:00",30,"T7����","2019.04.01","���軨Ů��","2019.05.01"},
//	{"B18111603","2019.01.01","20:00:00",60,"T9����","2019.04.01","���������塷","2019.05.01"},
//	{"B18111603","2019.01.24","13:00:00",120,"T12����","2019.04.01","������.�������ȡ�","2019.05.01"},	
//	{"B18111604","2019.01.01","20:00:00",60,"T9����","2019.04.01","��ˮ䰴���","2019.05.01"},
//	{"B18111604","2019.03.16","16:00:00",40,"T6����","2019.04.01","���������","2019.05.01"},
//	{"B18111605","2019.01.01","20:00:00",60,"T9����","2019.04.01","��ʷ�ǡ�","2019.05.01"},
//	{"B18111605","2019.01.09","21:00:00",20,"T9����","2019.04.01","��ţ򵡷","2019.05.01"}
//};

struct lostinformation
{
	char ID[10];
	char tel[20];
} Lostinformation[size];

void goto_xy(int x,int y)
{ 
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={x,y};
	SetConsoleCursorPosition(hout,pos);
}

void saveCardData(int n)
{
	FILE* fp;
	fp=fopen("��Ϣ\\�˺���Ϣ.dat","wb+");
	if (fp==0)
	{
		printf("ERROR\n");
		exit(1);
	}
	fwrite(Card,sizeof(struct card),n,fp);
	fclose(fp);
}

int readCardData()
{
	FILE* fp;
	fp=fopen("��Ϣ\\�˺���Ϣ.dat","rb");
	if (fp==0)
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(Card,sizeof(struct card),size,fp);
	fclose(fp);	
	return cnt;
}

int readLostInformation(struct lostinformation r[],int n)
{
	FILE *fp=fopen("��Ϣ\\ʧ��������Ϣ.dat","rb");
	if (fp==0)
	{
		printf("ERROR\n");
		exit(1);	
	}
	int cnt=fread(r,sizeof(struct lostinformation),n,fp);
	fclose(fp);
	return cnt;
} 

//void saveData()			//����������¼������ 
//{
//	int i,j;
//	char *s[5]={
//		"��Ϣ\\B18111601.dat","��Ϣ\\B18111602.dat","��Ϣ\\B18111603.dat","��Ϣ\\B18111604.dat","��Ϣ\\B18111605.dat"
//	};
//	for (i=0;i<5;i++)
//	{
//		for (j=0;j<10;j++)
//		{
//			if (strncmp(Record[j].ID,s[i],9)==0)
//			{
//				FILE* fp;
//				fp=fopen(s[i],"ab+");
//				if (fp==0)
//				{
//					printf("ERROR\n");
//					exit(1);
//				}
//				fwrite(&Record[j],sizeof(struct record),1,fp);
//				fclose(fp);
//			}
//		}
//
//	}
//}

void selectstatus();
int runselect();
int Adrlogin();
void Adrmenu();
int relieve();
void homepage();	//��ҳ 
int login(); 	//��½���棬����ֵΪ-1��ʾ��½ʧ�ܣ�Ϊ0��ʾB18111601���Դ����� 
void menu(int n);	//���˵� 
void refermenu(int n);	//��ѯ�˵� 
int recharge(int n);	//��ֵ���� 
int runrefer(int n);	//���ݲ�ѯ�˵���ѡ�������� 
void referremain(int n);//��ѯ��� 
void referWeb(int n);	//��ѯ������¼ 
void referbook(int n); 
int freeze();	//��ʧ���� 
void reset(int n);	//����������� 
void AutoMakeCard();
int freezemenu();
int findpassword(); 
void findLostCard();
void delLostInformation();
void referAllCard();
void referAllTime(int n);
void referAllCost(int n);

int signin()
{
	int judge=1; 
	do
	{
		system("cls");
		printf("\n		������ע��У԰�����棡\n");
		printf("		--------------------------------------------------\n");
		printf("		**************************************************\n");
		printf("		*                                                *\n");
		printf("		*  ��������ѧ��ݣ�                   (2001-2099)*\n");
		printf("		*                                                *\n");
		printf("		*  ����������ѧԺ���ţ�              ��01-11��   *\n");
		printf("		*                                                *\n");
		printf("		*  ���������ڰ༶��                  ��01-20��   *\n"); 
		printf("		*                                                *\n");
		printf("		*  ��������ʼѧ�ţ�                  ��01-99��   *\n");
		printf("		*                                                *\n");
		printf("		*  ��������ֹѧ�ţ�                  ��01-99��   *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*  ע������0�򷵻���һ����                       *\n");
		printf("		*                                                *\n");
		printf("		**************************************************\n");
		char year[5];
		char academy[5];
		char Class[5];
		int begin;
		int end; 
		int i,j;
		char s[50];
		goto_xy(35,5);
		scanf("%4s",year);
		if (strcmp(year,"0")==0) judge=0;
		else
		{
			int yearnum=0;
			for (i=0;i<strlen(year);i++)
			{
				yearnum=yearnum*10+(year[i]-'0');
			}
			if (yearnum<=2000 || yearnum>=2100) 
			{
				printf("\n\n\n\n\n\n\n\n\n		*  ��ݴ���\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(39,7);
			scanf("%2s",academy);
			int acadnum=0;
			for (i=0;i<strlen(academy);i++)
			{
				acadnum=acadnum*10+(academy[i]-'0');
			}
			if (acadnum<=0 || acadnum>=12) 
			{
				printf("\n\n\n\n\n\n\n\n		*  ѧԺ���Ų����ڣ�\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,9);
			scanf("%2s",Class);
			int classnum=0;
			for (i=0;i<strlen(Class);i++)
			{
				classnum=classnum*10+(Class[i]-'0');
			}
			if (classnum<=0 || classnum>=21) 
			{
				printf("\n\n\n\n\n\n		*  �༶����\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,11);
			scanf("%d",&begin);
			if (begin<=0 || begin>=100) 
			{
				printf("\n\n\n\n		*  ��ʼѧ�Ŵ���\n");
				Sleep(2000);
				continue;
			}
			goto_xy(35,13);
			scanf("%d",&end);
			if (end<=0 || end>=100) 
			{
				printf("\n\n		*  ��ֹѧ�Ŵ���\n");
				Sleep(2000);
				continue;
			}
			if (end<begin) 
			{
				printf("\n		*  ��ֹѧ�Ų���С����ʼѧ�ţ�\n");
				Sleep(2000);
				continue;
			}
			char *p=year+2;
			struct card tcard[end-begin+1];
			for (i=0;i<end-begin+1;i++)
			{
				sprintf(s,"%s%s%s%s%02d","B",p,academy,Class,begin+i);
				strcpy(tcard[i].ID,s);
			}
			int flag=1;
			for (i=0;i<end-begin+1;i++)
			{
				for (j=0;j<count;j++) 
					if (strcmp(tcard[i].ID,Card[j].ID)==0)
					{
						flag=0;
						break;
					}
				if (flag==0) break;
			}
			if (flag)
			{
				printf("\n\n\n\n\n\n\n\n\n");
				printf("\n		   �������������������֤��4λ��\n");
				for (i=0;i<end-begin+1;i++)
				{
					tcard[i].remain=100;
					tcard[i].state=0;
					strcpy(tcard[i].password,"888888");
					printf("		   ");
					scanf("%10s %5s",tcard[i].name,tcard[i].idcard);
				}
				for (i=0;i<end-begin+1;i++)
				{
					sprintf(s,"%s%s.dat","��Ϣ\\",tcard[i].ID);
					FILE *fp=fopen(s,"wb+");
					if (fp==0)
					{
						printf("ERROR\n");
						exit(1);
					}
					fclose(fp);
				}
				FILE *fp=fopen("��Ϣ\\�˺���Ϣ.dat","ab+");
				if (fp==0)
				{
					printf("ERROR\n");
					exit(1);
				}
				fwrite(tcard,sizeof(struct card),end-begin+1,fp);
				fclose(fp);	
				printf("\n\n		   ע��ɹ���\n");
				judge=2;
			}
			else
			{
				printf("\n		*  ���������Ѵ��ڣ��޷�ע�ᣡ\n");
				Sleep(2000);
			}		
		}
	} while (judge==1);
	return judge;
}

void del()
{
	int flag=1;
	do
	{
		system("cls");
		printf("\n		������ɾ��У԰�����棡\n");
		printf("		--------------------------------------------------\n");
		printf("		**************************************************\n");
		printf("		*                                                *\n");
		printf("		*  ��������ѧ��ݣ�                   (2001-2099)*\n");
		printf("		*                                                *\n");
		printf("		*  ����������ѧԺ���ţ�              ��01-11��   *\n");
		printf("		*                                                *\n");
		printf("		*  ���������ڰ༶��                  ��01-20��   *\n"); 
		printf("		*                                                *\n");
		printf("		*  ��������ʼѧ�ţ�                  ��01-99��   *\n");
		printf("		*                                                *\n");
		printf("		*  ��������ֹѧ�ţ�                  ��01-99��   *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*  ע������0�򷵻���һ����                       *\n");
		printf("		*                                                *\n");
		printf("		**************************************************\n");
		char year[5];
		char academy[5];
		char Class[5];
		int begin;
		int end; 
		int i,j,k;
		goto_xy(35,5);
		scanf("%4s",year);
		if (strcmp("0",year)==0) 
		{
			flag=0;
			system("cls");
		}
		else
		{
			int yearnum=0;
			for (i=0;i<strlen(year);i++)
			{
				yearnum=yearnum*10+(year[i]-'0');
			}
			if (yearnum<=2000 || yearnum>=2100) 
			{
				printf("\n\n\n\n\n\n\n\n\n		*  ��ݴ���\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(39,7);
			scanf("%2s",academy);
			int acadnum=0;
			for (i=0;i<strlen(academy);i++)
			{
				acadnum=acadnum*10+(academy[i]-'0');
			}
			if (acadnum<=0 || acadnum>=12) 
			{
				printf("\n\n\n\n\n\n\n\n		*  ѧԺ���Ų����ڣ�\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,9);
			scanf("%2s",Class);
			int classnum=0;
			for (i=0;i<strlen(Class);i++)
			{
				classnum=classnum*10+(Class[i]-'0');
			}
			if (classnum<=0 || classnum>=21) 
			{
				printf("\n\n\n\n\n\n		*  �༶����\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,11);
			scanf("%d",&begin);
			if (begin<=0 || begin>=100) 
			{
				printf("\n\n\n\n		*  ��ʼѧ�Ŵ���\n");
				Sleep(2000);
				continue;
			}
			goto_xy(35,13);
			scanf("%d",&end);
			if (end<=0 || end>=100) 
			{
				printf("\n\n		*  ��ֹѧ�Ŵ���\n");
				Sleep(2000);
				continue;
			}
			if (end<begin) 
			{
				printf("\n		*  ��ֹѧ�Ų���С����ʼѧ�ţ�\n");
				Sleep(2000);
				continue;
			}
			char *p=year+2;
			char s[50];
			int judge;
			int sign=1;
			for (i=0;i<end-begin+1;i++)
			{
				judge=0;
				sprintf(s,"%s%s%s%s%02d","B",p,academy,Class,i+begin);
				for (j=0;j<count;j++)
				{
					if (strcmp(s,Card[j].ID)==0)
					{
						judge=1;
						for (k=j;k<count-1;k++)
						{
							Card[k]=Card[k+1];
						}
						break;
					}
				}
				if (judge)
				{
					sprintf(s,"%s%s.dat","��Ϣ\\",s);
					remove(s);	
				}
				else
				{
					sign=0;
					printf("\n		*  �������ݲ����ڣ��޷�ɾ����\n");
					Sleep(2000);
					system("cls");
					break;
				}
			}
			if (sign)
			{
				for (i=0;i<count-1;i++)
				{
					if (strcmp(Card[i].ID,Card[i+1].ID)==0) break;
				}
				saveCardData(i);
				count=i;
				printf("\n		*  ɾ���ɹ���\n");
				Sleep(2000);
				system("cls");
				flag=0;
			}
		}
	} while (flag);
}

int main()
{
//	saveCardData(5);
	count=readCardData();
//	saveData();	//����������¼������ 
	int key;	//��½�󣬴�ſ����������е�λ�� 
	do
	{
		homepage();
		selectstatus();
		switch (runselect())
		{
			case 1:	if (Adrlogin()==0) 
					{
						Sleep(2000);
						system("cls");
						continue;
					}
					Sleep(2000);
					system("cls");
					int mark; 
					do
					{
						Adrmenu();
						mark=runselect();
						if (mark==1) 
						{
							if (signin())
							{
								count=readCardData();
								Sleep(2000);
								system("cls");
							}
							else
							{
								system("cls");
								continue;	
							}	
						}
						else if (mark==2) 
						{
							del();
						}
						else if (mark==3)
						{
							referAllCard();
						}
					} while (mark);
					if (mark==0)
					{
						system("cls");
					}
					break;
			case 2:	key=login();
					if (key<0) 
					{
						Sleep(2000);
						system("cls");
						continue;
					}//С��0��ʾ��½ʧ�� 
					else
					{
						Sleep(2000);
						system("cls");
						do 
						{
							menu(key);	//��½�ɹ���������˵� 
							int choice; 
							int judge=0;//��ʧ���޸���������µ�½ 
							printf("\n		���������ѡ��");
							scanf("%d",&choice);
							system("cls");
							int flag;
							int i; 
							switch (choice)
							{
								case 0:break;	//ѡ��0��ʾ�˳���½ 
								case 1:	
										do
										{
											refermenu(key);	//ѡ��1�����ѯ�˵� 
											flag=runrefer(key);	//���ݲ�ѯ�˵���ѡ�������� 
											system("cls");
										} while (flag);
										break;
								case 2:	if (recharge(key))
										{
											Sleep(2000);
											system("cls");
										}
										else system("cls");	
										break;	//ѡ��2�����ֵ���� 
								case 3:	reset(key);
										judge=1;	 
										Sleep(2000);
										system("cls");
										break;
								case 4:	findLostCard();
										system("cls");
										break;
								case 5: delLostInformation();
										system("cls");
										break;
								default:continue;
							}
							
							if (choice==0) break;
							if (judge) break;
						} while (1);	
					}
					break;
			case 3: system("cls");
					AutoMakeCard();
					system("cls");
					break;
			case 4: system("cls");
					int select=freezemenu();
					while (select)
					{
						system("cls");
						select=freezemenu();
					}
					system("cls");
					break;
			case 5:	if (!findpassword()) Sleep(2000);
					system("cls");
					break;
			default:system("cls");
		}
	} while (1);
	return 0;
}

void homepage()
{
	struct lostinformation r[size];
	int cnt=readLostInformation(r,size);
	printf("		******************************************\n");
	printf("		*  ʧ������С�ڰ�                        *\n");
	int i;
	int k=0;
	for (i=cnt-1;i>=0;i--)
	{
		if (k>=3) break;
		k++;
		printf("		*  %d��%s  ��ʧ����ϵ %11s  *\n",k,r[i].ID,r[i].tel);
	} 
	if (k==0) printf("		*  ������Ϣ                              *\n");
	printf("		******************************************\n");
	printf("		------------------------------------------\n");
}

void selectstatus()
{
	printf("		******************************************\n");
	printf("		*           ��ѡ���ܣ�                 *\n");
	printf("		*           1������Ա��½                *\n");
	printf("		*           2��ѧ����½                  *\n");
	printf("		*           3����������                  *\n");
	printf("		*           4����ʧ������ʧ            *\n");
	printf("		*           5����������                  *\n");
	printf("		******************************************\n\n");
}

int runselect()
{
	int choice=0;
	printf("\n		���������ѡ��");
	scanf("%d",&choice);
	return choice;
}

int Adrlogin()
{
	int judge=0;
	char id[10];
	char pass[20];
	int i;
	printf("\n		�������˺ţ�");
	scanf("%10s",id);
	printf("\n		���������룺");
	for (i=0;i<20;i++) 
	{
		pass[i]=getch();
		
		if (pass[i]=='\r') 
		{
			pass[i]='\0';
			break;
		}
		else if (pass[i]==8) 
		{
			printf("\b \b");
			i-=2;
		}
		else printf("*");
	}
	printf("\n");
	if (strcmp(id,Adr.ID)) printf("\n		�˺Ų����ڣ�\n\n");
	else
	{
		if (strcmp(pass,Adr.password)) printf("\n		�������\n\n");
		else 
		{
			judge=1;
			printf("\n		��½�ɹ���\n\n");
		}
	}	
	return judge;	
}

void Adrmenu()
{
	printf("\n		���ǹ���Ա��\n");
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*      ��ѡ���ܣ�          *\n");
	printf("		*      1��ע��У԰��         *\n");
	printf("		*      2��ɾ��У԰��         *\n");
	printf("		*      3����ѯ����У԰��     *\n");
	printf("		*      0���˳�               *\n");
	printf("		******************************\n\n");
} 

int relieve()
{
	system("cls");
	char id[10];
	int judge=1;
	int i;
	int sign=0;
	char pass[20];
	do
	{
		printf("\n		�����ǽⶳ���棡\n");
		printf("		----------------------------\n");
		printf("		****************************\n");
		printf("		*  Ŀǰ�ѹ�ʧ��У԰����    *\n");
		int j;
		int k=0;
		for (j=0;j<count;j++)
		{
			if (Card[j].state) printf("		* %2d��%s  %-10s*\n",++k,Card[j].ID,Card[j].name);
		} 
		if (k==0) printf("		*             ��           *\n");
		printf("		****************************\n");
		printf("\n		--------------------------------------------\n");
		printf("\n		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  ������Ҫ��������У԰���ţ�            *\n");
		printf("		*                                          *\n");
		printf("		*  ���������룺                            *\n");
		printf("		*                                          *\n");
	    printf("		*                                          *\n");
	    printf("		*                                          *\n");
	    printf("		*                                          *\n");
		printf("		*  ע������0�򷵻���һ������               *\n");
		printf("		*                                          *\n");	
		printf("		********************************************\n");
		goto_xy(47,11+k);
		scanf("%10s",id);
		if (strcmp(id,"0")==0) sign=1;
		else 
		{
			goto_xy(31,13+k);
			for (i=0;i<20;i++) 
			{
				pass[i]=getch();
				if (pass[i]=='\r') 
				{
					pass[i]='\0';
					break;
				}
				else if (pass[i]==8) 
				{
					printf("\b \b");
					i-=2;
				}
				else printf("*");
			}
			printf("\n"); 
			for (i=0;i<count;i++) 
				if (strcmp(id,Card[i].ID)==0)
				{
					judge=0;
					break;
				}
			if (judge)
			{	
				printf("\n		*  ���˻������ڣ�\n\n");
				Sleep(2000);
				system("cls");
			}
			else if (strcmp(pass,Card[i].password)==0)
			{
				if (Card[i].state==0)
				{
					printf("\n		*  ���˻�δ��ʧ��\n\n");
					Sleep(2000);
					system("cls");
				} 
				else
				{
					Card[i].state=0;
					printf("\n		*  �������ɹ���\n\n");
					sign=2;
					saveCardData(count);
					Sleep(2000);
					system("cls");
				}
			}
			else
			{
				printf("\n		*  �������\n\n");
				Sleep(2000);
				system("cls");
			}
		}
	} while (!sign);
	return sign;
}

int login()
{
	static int cnt[size]={0};

	int i;
	int k=-1; 
	int judge=0;
	char id[10];
	char pass[20];
	printf("\n		�������˺ţ�");
	scanf("%10s",id);
	printf("\n		���������룺");
	for (i=0;i<20;i++) 
	{
		pass[i]=getch();
		
		if (pass[i]=='\r') 
		{
			pass[i]='\0';
			break;
		}
		else if (pass[i]==8) 
		{
			printf("\b \b");
			i-=2;
		}
		else printf("*");
	}
	printf("\n");
	for (i=0;i<count && judge==0;i++)
		if (strcmp(id,Card[i].ID)==0)
		{
			judge=1;
			if (strcmp(pass,Card[i].password)==0)
			{
				if (Card[i].state==0) 
				{
					k=i;
					printf("\n		��½�ɹ���\n\n");
				}
				else printf("\n		�����˻��Ѷ��ᣡ\n\n");
				break;
			} 
			else 
			{
				printf("\n		�������\n");
				cnt[i]++;
				switch (cnt[i])
				{
					case 1:printf("\n		������2��������ᣡ\n\n");break;
					case 2:printf("\n		������1��������ᣡ\n\n");break;
					default:break;
				}
				if (cnt[i]>=3) 
				{
					Card[i].state=1;
					saveCardData(count);
					printf("\n		�����˻��Ѷ��ᣡ\n\n");break;
					cnt[i]=0;
				}
			}
		}
	if (judge==0) printf("\n		�˺Ų����ڣ�\n\n");
	return k;
}

void menu(int n)
{
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*    ��ѡ���ܣ�            *\n");
	printf("		*    1����ѯ                 *\n");
	printf("		*    2����ֵ                 *\n");
	printf("		*    3����������             *\n");
	printf("		*    4���Ǽ�ʧ��������Ϣ     *\n");
	printf("		*    5��ɾ��ʧ��������Ϣ     *\n");	
	printf("		*    0���˳�                 *\n");
	printf("		******************************\n\n");
}

void refermenu(int n)
{
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*       ��ѡ���ܣ�         *\n");
	printf("		*       1����ѯ���          *\n");
	printf("		*       2����ѯ������¼      *\n");
	printf("		*       3����ѯ������ʱ��    *\n");
	printf("		*       4����ѯ�����ܷ���    *\n");
	printf("		*       5����ѯ���ļ�¼      *\n");
	printf("		*       0������              *\n");
	printf("		******************************\n\n");
}


int recharge(int n)
{	
	int amount;
	do
	{
		printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
		printf("		----------------------------\n");
		printf("\n		�������ֵ��"); 
		printf("\n\n\n\n		ע������0�򷵻���һ���棡\n");
		goto_xy(32,4);
		scanf("%d",&amount);
		if (amount>0 && amount<=500) 
		{
			Card[n].remain+=amount*1.0;
			saveCardData(count);
			printf("\n		��ֵ�ɹ���\n\n");
			Sleep(2000);
			system("cls");
			printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
			printf("		----------------------------\n");
			printf("		��Ŀǰ�����Ϊ��%.2f\n\n",Card[n].remain);
			int i;
			for (i=5;i>0;i--)
			{ 
				printf("		ϵͳ����%d���Ϊ��������һ������\r",i);
				Sleep(1000);
			}
		}
		else if (amount==0) break;
		else
		{
			printf("\n		�����������\n\n");
			Sleep(2000);
			system("cls");
		}
	} while (amount<0);
	return amount;
} 

int runrefer(int n)
{
	int choice;
	printf("\n		���������ѡ��");
	scanf("%d",&choice);
	switch (choice)
	{
		case 0:break;
		case 1:referremain(n);break;
		case 2:referWeb(n);break;
		case 3:referAllTime(n);break;
		case 4:referAllCost(n);break;
		case 5:referbook(n);break;
	}
	return choice;
}

void referremain(int n)
{
	system("cls");
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		�������Ϊ��%.2f\n",Card[n].remain); 
	printf("		----------------------------\n\n");
	printf("\n		ע�����س������أ�\n");
	printf("		");
	getchar(); 
	getchar();
}

void referWeb(int n)
{
	system("cls");
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		----------------------------\n");
	struct record r[3];
	char s[50];
	sprintf(s,"%s%s.dat","��Ϣ\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),3,fp);
	printf("\n		����������¼Ϊ��\n");
	int i;
	int judge=1;
	printf("\n		��������    ��ʼʱ��  ����ʱ��  �����ص�  ������������\n");
	for (i=0;i<cnt;i++)
	{
		judge=0;
		printf("\n		%s  %s  %d(��)     %s    %.2f��Ԫ��\n",r[i].date,r[i].start_time,r[i].duration,r[i].place,r[i].duration*0.2/60);
	}
	if (judge) printf("\n		���޼�¼��\n");
	fclose(fp);
	printf("\n\n		ע�����س������أ�\n");
	getchar();
	getchar();
}

void referbook(int n)
{
	system("cls");
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		----------------------------\n");
	struct record r[3];
	char s[50];
	sprintf(s,"%s%s.dat","��Ϣ\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),3,fp);
	printf("\n		���Ľ��ļ�¼Ϊ��\n");
	int i;
	int judge=1;
	printf("\n		��������       ��������     �����ֹ����\n");
	for (i=0;i<cnt;i++)
	{
		judge=0;
		printf("\n		%s    %-12s%14s\n",r[i].Book.when,r[i].Book.bookname,r[i].Book.deadline);
	}
	if (judge) printf("\n		���޼�¼��\n");
	fclose(fp);
	printf("\n\n		ע�����س������أ�\n");
	getchar();
	getchar();
}

int freeze()
{
	int judge=0;
	int sign=1;
	do
	{
		system("cls");
		printf("\n		�����ǹ�ʧ������ʧ���棡\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  ��������Ҫ��ʧ��У԰���ţ�         *\n");
		printf("		*                                     *\n");
		printf("		*  ���������룺                       *\n");	
		printf("		*                                     *\n"); 
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*  ע������0�򷵻���һ����            *\n");
		printf("		*                                     *\n");	
		printf("		***************************************\n");
		char id[10];
		char pass[20];
		int i;
		goto_xy(45,5);
		scanf("%10s",id);
		if (strcmp("0",id)==0) break;
		goto_xy(31,7); 
		for (i=0;i<20;i++) 
		{
			pass[i]=getch();
			
			if (pass[i]=='\r') 
			{
				pass[i]='\0';
				break;
			}
			else if (pass[i]==8) 
			{
				printf("\b \b");
				i-=2;
			}
			else printf("*");
		}
		printf("\n");
		for (i=0;i<count && judge==0;i++)
			if (strcmp(id,Card[i].ID)==0)
			{
				judge=1;
				if (strcmp(pass,Card[i].password)==0)
				{
					if (Card[i].state==0) 
					{
						Card[i].state=1;
						saveCardData(count); 
						printf("\n		*  ��ʧ�ɹ���\n\n");
						sign=0;
						Sleep(2000);
						system("cls");
					}
					else 
					{
						printf("\n		*  �����˻��ѹ�ʧ��\n\n");
						Sleep(2000);
						system("cls");
					}
					break;
				} 
				else 
				{
					printf("\n		*  �������\n\n");
					Sleep(2000);
					system("cls");
				}
			}
		if (judge==0) 
		{
			printf("\n		*  �˺Ų����ڣ�\n\n");
			Sleep(2000);
			system("cls");
		}
	} while (sign);
	return 1;
}

void reset(int n)
{
	char newpass[20];
	char newpass1[20];
	int i;
	do
	{
		printf("\n		����������������棡\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  �����������룺                     *\n");
		printf("		*                                     *\n");
		printf("		*  ���ٴ����������룺                 *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		***************************************\n");
		goto_xy(33,5);
		for (i=0;i<20;i++) 
		{
			newpass[i]=getch();
			
			if (newpass[i]=='\r') 
			{
				newpass[i]='\0';
				break;
			}
			else if (newpass[i]==8) 
			{
				printf("\b \b");
				i-=2;
			}
			else printf("*");
		}
		goto_xy(37,7);
		for (i=0;i<20;i++) 
		{
			newpass1[i]=getch();
			
			if (newpass1[i]=='\r') 
			{
				newpass1[i]='\0';
				break;
			}
			else if (newpass1[i]==8) 
			{
				printf("\b \b");
				i-=2;
			}
			else printf("*");
		}
		printf("\n");
		if (strcmp(newpass,newpass1)) 
		{
			printf("\n		*  �������벻һ�£����������룡\n\n");
			Sleep(2000);
			system("cls"); 
		}
	} while (strcmp(newpass,newpass1));
	strcpy(Card[n].password,newpass);
	saveCardData(count);
	printf("\n		*  ��������ɹ���\n\n");
}

void AutoMakeCard()
{
	int sign=1;
	do
	{
		printf("\n		���������������նˣ�\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  ��������Ҫ�����У԰���ţ�              *\n");
		printf("		*                                          *\n");
		printf("		*  ���������룺                            *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*  ע������0�򷵻���һ������               *\n");
		printf("		*                                          *\n");
		printf("		********************************************\n");
		char id[10];
		char pass[20];
		int i;
		goto_xy(45,5);
		scanf("%10s",id);
		if (strcmp(id,"0")==0) break;
		goto_xy(31,7);
		for (i=0;i<20;i++) 
		{
			pass[i]=getch();
			
			if (pass[i]=='\r') 
			{
				pass[i]='\0';
				break;
			}
			else if (pass[i]==8) 
			{
				printf("\b \b");
				i-=2;
			}
			else printf("*");
		}
		printf("\n");
		int judge=0;
		for (i=0;i<count;i++) 
		{
			if (strcmp(id,Card[i].ID)==0) 
			{
				judge=1;
				break;
			}
		}
		if (judge==0) 
		{
			printf("\n		*  �˻������ڣ�\n\n");
			Sleep(2000);
			system("cls");
			continue;
		}
		else if (strcmp(pass,Card[i].password)) 
		{
			printf("\n		*  �������\n\n");
			Sleep(2000);
			system("cls");
			continue;
		}
		else 
		{
			sign=0;
			printf("\n		*  ���Ժ�\n");
			int j;
			for (j=5;j>0;j--)
			{	
				Sleep(2000);
				printf("		*  %d\n",j);
			}
			Card[i].state=0;
			Card[i].remain-=25.0;
			saveCardData(count);
			printf("\n		*  �����ɹ���\n\n");
			Sleep(2000);
		} 
	} while (sign);
	
}

int freezemenu()
{
	int judge=1;
	printf("\n		�����ǹ�ʧ������ʧ���棡\n");
	printf("		--------------------------------------\n");
	printf("		**************************************\n");
	printf("		*                                    *\n");
	printf("		*        ��ѡ���ܣ�                *\n");
	printf("		*        1����ʧ                     *\n");
	printf("		*        2�������ʧ                 *\n"); 
	printf("		*        0������                     *\n");
	printf("		*                                    *\n");
	printf("		**************************************\n");
	int choice;
	choice=runselect();
	switch (choice)
	{
		case 0:judge=0;break;
		case 1:judge=freeze();break;
		case 2:judge=relieve();break;
	} 
	return judge;
}

int findpassword()
{
	int flag=0;
	do
	{
		system("cls");
		printf("\n		�������һ�������棡\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  ������У԰���ţ�                   *\n");
		printf("		*                                     *\n");
		printf("		*  ������������                       *\n");
		printf("		*                                     *\n");
		printf("		*  ���������֤��4λ��                *\n"); 
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*  ע������0�򷵻���һ����            *\n");
		printf("		*                                     *\n");
		printf("		***************************************\n");
		char id[10];
		char name[10];
		char idcard[5];
		goto_xy(35,5);
		scanf("%10s",id);
		if (strcmp("0",id)==0) 
		{
			flag=1;
			break;
		}
		else
		{
			goto_xy(31,7);
			scanf("%10s",name);
			goto_xy(38,9);
			scanf("%4s",idcard);
			int i;
			int judge=0;
			for (i=0;i<count;i++)
			{
				if (strcmp(Card[i].ID,id)==0) 
				{
					judge=1;
					break;
				}
			}
			if (judge)
			{
				if (strcmp(Card[i].name,name)==0 && strcmp(Card[i].idcard,idcard)==0)
				{
					printf("\n		*  ��Ϣ��֤�ɹ���\n");
					Sleep(2000);
					system("cls");
					reset(i);
					break;
				}
				else
				{
					printf("\n		*  ��Ϣ����\n");
					Sleep(2000);
					system("cls");
				}
			}
			else
			{
				printf("\n		*  �˺Ų����ڣ�\n");
				Sleep(2000);
				system("cls");
			}
		}
	} while (1);
	return flag;
}

void findLostCard()
{
	int judge=1;
	do
	{
		char id[10];
		char tel[20]; 
		system("cls");
		printf("\n		������ʧ��������棡\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  ��������񵽵�У԰���ţ�                *\n");
		printf("		*                                          *\n");
		printf("		*  ��������ĵ绰���룺                    *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*  ע������0�򷵻���һ������               *\n");
		printf("		*                                          *\n");
		printf("		********************************************\n");
		goto_xy(43,5);
		scanf("%10s",id);
		if (strcmp("0",id)==0) judge=0;
		else
		{
			goto_xy(39,7);
			scanf("%20s",tel);
			if (strlen(tel)!=11 || tel[0]!='1') 
			{
				printf("\n		*  ��������ȷ�ĵ绰���룡\n");
				Sleep(2000);
				continue;
			} 
			int i;
			int flag=0;
			int sign=1;
			for (i=0;i<count;i++)
			{
				if (strcmp(Card[i].ID,id)==0)
				{
					flag=1;
					break;
				}
			}
			struct lostinformation rt[size];
			int cnt=readLostInformation(rt,size);
			for (i=0;i<cnt;i++)
			{
				if (strcmp(rt[i].ID,id)==0)
				{
					sign=0;
					break;
				}
			}
			if (flag && sign)
			{
				judge=0; 
				struct lostinformation r;
				strcpy(r.ID,id);
				strcpy(r.tel,tel);
				FILE *fp=fopen("��Ϣ\\ʧ��������Ϣ.dat","ab+");
				if (fp==0)
				{
					printf("ERROR\n");
					exit(1);	
				}
				fwrite(&r,sizeof(struct lostinformation),1,fp);
				fclose(fp);
				printf("\n		*  �Ǽǳɹ���\n");
				Sleep(2000);
			}
			else if (flag==0)
			{
				printf("\n		*  �ÿ��Ų����ڣ�\n");
				Sleep(2000); 
			}
			else 
			{
				printf("\n		*  �ÿ�������ʧ��������Ϣ�У�\n");
				Sleep(2000);
			}
		}
	} while (judge);	
}

void delLostInformation()
{
	int sign=1;
	int cnt;
	do
	{
		system("cls");
		printf("\n		������ɾ��ʧ��������Ϣ���棡\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  ������У԰���ţ�                        *\n");
		printf("		*                                          *\n");
		printf("		*  ���������룺                            *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*  ע������0�򷵻���һ������               *\n");
		printf("		*                                          *\n");
		printf("		********************************************\n");
		char id[10];
		char pass[20];
		int i;
		goto_xy(35,5);
		scanf("%10s",id);
		if (strcmp(id,"0")==0) break;
		goto_xy(31,7);
		for (i=0;i<20;i++) 
		{
			pass[i]=getch();
			
			if (pass[i]=='\r') 
			{
				pass[i]='\0';
				break;
			}
			else if (pass[i]==8) 
			{
				printf("\b \b");
				i-=2;
			}
			else printf("*");
		}
		printf("\n");
		int flag=0;
		for (i=0;i<count;i++)
		{
			if (strcmp(Card[i].ID,id)==0)
			{
				flag=1;
				break;
			}
		}
		if (flag)
		{
			if (strcmp(Card[i].password,pass)==0)
			{
				FILE *fp=fopen("��Ϣ\\ʧ��������Ϣ.dat","rb");
				if (fp==0)
				{
					printf("ERROR\n");
					exit(1);	
				}
				cnt=fread(Lostinformation,sizeof(struct lostinformation),size,fp);
				int j,k;
				int judge=0;
				for (j=0;j<cnt;j++)
				{
					if (strcmp(Card[i].ID,Lostinformation[j].ID)==0)
					{
						judge=1;
						break;
					}
				}
				if (judge) 
				{
					for (k=j;k<cnt-1;k++)
					{
						Lostinformation[k]=Lostinformation[k+1];
					}
					fp=fopen("��Ϣ\\ʧ��������Ϣ.dat","wb+");
					if (fp==0)
					{
						printf("ERROR\n");
						exit(1);	
					}
					fwrite(Lostinformation,sizeof(struct lostinformation),cnt-1,fp);
					fclose(fp);
					printf("\n		*  ɾ���ɹ���\n");
					sign=0;
					Sleep(2000);
				}
				else
				{
					printf("\n		*  ����У԰������ʧ��������Ϣ�У�\n");
					Sleep(2000);
					continue;
				} 
			}
			else
			{
				printf("\n		*  �������\n");
				Sleep(2000);
				continue;
			}
		}
		else
		{
			printf("\n		*  �˺Ų����ڣ�\n");
			Sleep(2000);
			continue;	
		} 
	} while (sign); 
}

void referAllCard()
{
	system("cls");
	printf("\n		���ǹ���Ա��\n");
	printf("		---------------------------------------\n");
	printf("		***************************************\n");
	printf("		*                                     *\n");
	printf("		*  Ŀǰ��ע���У԰����               *\n");
	int i;
	for (i=0;i<count;i++)
	{
		printf("		* %2d��%s  %-21s*\n",i+1,Card[i].ID,Card[i].name);
	} 
	printf("		*                                     *\n");
	printf("		*  ע�����س������أ�                 *\n");
	printf("		*                                     *\n");
	printf("		***************************************\n");
	getchar();
	getchar();
	system("cls"); 
}

void referAllTime(int n)
{
	struct record r[size];
	char s[50];
	sprintf(s,"%s%s.dat","��Ϣ\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),size,fp);
	int sum=0;
	int i;
	for (i=0;i<cnt;i++) sum+=r[i].duration;
	fclose(fp);
	system("cls");
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		����������ʱ��Ϊ��%d���֣�\n",sum); 
	printf("		----------------------------\n\n");
	printf("\n		ע�����س������أ�\n");
	printf("		");
	getchar(); 
	getchar();
} 

void referAllCost(int n)
{
	struct record r[size];
	char s[50];
	sprintf(s,"%s%s.dat","��Ϣ\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),size,fp);
	double sum=0;
	int i;
	for (i=0;i<cnt;i++) sum+=r[i].duration*0.2/60;
	fclose(fp);
	system("cls");
	printf("\n		���Ŀ���Ϊ��%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		���������ܷ���Ϊ��%.2f��Ԫ��\n",sum); 
	printf("		----------------------------\n\n");
	printf("\n		ע�����س������أ�\n");
	printf("		");
	getchar(); 
	getchar();
} 
