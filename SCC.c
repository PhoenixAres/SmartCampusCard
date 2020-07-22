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
	char idcard[5];	//身份证号  为方便表示，用后4位表示 
	double remain;	//余额 
	int state;		//0表示正常，1表示冻结 
} Card[size];
//={
//	{"张XX","B18111601","888888","0123",95,1}, 
//	{"李XX","B18111602","888888","1234",83,0},
//	{"王XX","B18111603","888888","2345",52,0},
//	{"朱XX","B18111604","888888","3456",46,0},
//	{"邓XX","B18111605","888888","4567",71,0} 
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
	char date[20];		//上网日期 
	char start_time[20];//开始时间 
	int duration;		//单次上网时长 
	char place[20];		//上网地点
	struct book Book;
};
//Record[10]={
//	{"B18111601","2019.01.01","20:00:00",60,"T9机房","2019.04.01","《红楼梦》","2019.05.01"},
//	{"B18111601","2019.01.03","19:00:00",90,"T8机房","2019.04.01","《双城记》","2019.05.01"},
//	{"B18111602","2019.01.01","20:00:00",60,"T9机房","2019.04.01","《悲惨世界》","2019.05.01"},
//	{"B18111602","2019.02.01","09:00:00",30,"T7机房","2019.04.01","《茶花女》","2019.05.01"},
//	{"B18111603","2019.01.01","20:00:00",60,"T9机房","2019.04.01","《三国演义》","2019.05.01"},
//	{"B18111603","2019.01.24","13:00:00",120,"T12机房","2019.04.01","《安娜.卡列宁娜》","2019.05.01"},	
//	{"B18111604","2019.01.01","20:00:00",60,"T9机房","2019.04.01","《水浒传》","2019.05.01"},
//	{"B18111604","2019.03.16","16:00:00",40,"T6机房","2019.04.01","《理想国》","2019.05.01"},
//	{"B18111605","2019.01.01","20:00:00",60,"T9机房","2019.04.01","《史记》","2019.05.01"},
//	{"B18111605","2019.01.09","21:00:00",20,"T9机房","2019.04.01","《牛虻》","2019.05.01"}
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
	fp=fopen("信息\\账号信息.dat","wb+");
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
	fp=fopen("信息\\账号信息.dat","rb");
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
	FILE *fp=fopen("信息\\失物招领信息.dat","rb");
	if (fp==0)
	{
		printf("ERROR\n");
		exit(1);	
	}
	int cnt=fread(r,sizeof(struct lostinformation),n,fp);
	fclose(fp);
	return cnt;
} 

//void saveData()			//存入上网记录等数据 
//{
//	int i,j;
//	char *s[5]={
//		"信息\\B18111601.dat","信息\\B18111602.dat","信息\\B18111603.dat","信息\\B18111604.dat","信息\\B18111605.dat"
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
void homepage();	//主页 
int login(); 	//登陆界面，返回值为-1表示登陆失败，为0表示B18111601，以此类推 
void menu(int n);	//主菜单 
void refermenu(int n);	//查询菜单 
int recharge(int n);	//充值界面 
int runrefer(int n);	//根据查询菜单的选择结果运行 
void referremain(int n);//查询余额 
void referWeb(int n);	//查询上网记录 
void referbook(int n); 
int freeze();	//挂失界面 
void reset(int n);	//重置密码界面 
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
		printf("\n		这里是注册校园卡界面！\n");
		printf("		--------------------------------------------------\n");
		printf("		**************************************************\n");
		printf("		*                                                *\n");
		printf("		*  请输入入学年份：                   (2001-2099)*\n");
		printf("		*                                                *\n");
		printf("		*  请输入所在学院代号：              （01-11）   *\n");
		printf("		*                                                *\n");
		printf("		*  请输入所在班级：                  （01-20）   *\n"); 
		printf("		*                                                *\n");
		printf("		*  请输入起始学号：                  （01-99）   *\n");
		printf("		*                                                *\n");
		printf("		*  请输入终止学号：                  （01-99）   *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*  注：输入0则返回上一界面                       *\n");
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
				printf("\n\n\n\n\n\n\n\n\n		*  年份错误！\n");
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
				printf("\n\n\n\n\n\n\n\n		*  学院代号不存在！\n");
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
				printf("\n\n\n\n\n\n		*  班级错误！\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,11);
			scanf("%d",&begin);
			if (begin<=0 || begin>=100) 
			{
				printf("\n\n\n\n		*  起始学号错误！\n");
				Sleep(2000);
				continue;
			}
			goto_xy(35,13);
			scanf("%d",&end);
			if (end<=0 || end>=100) 
			{
				printf("\n\n		*  终止学号错误！\n");
				Sleep(2000);
				continue;
			}
			if (end<begin) 
			{
				printf("\n		*  终止学号不能小于起始学号！\n");
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
				printf("\n		   请依次输入姓名与身份证后4位：\n");
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
					sprintf(s,"%s%s.dat","信息\\",tcard[i].ID);
					FILE *fp=fopen(s,"wb+");
					if (fp==0)
					{
						printf("ERROR\n");
						exit(1);
					}
					fclose(fp);
				}
				FILE *fp=fopen("信息\\账号信息.dat","ab+");
				if (fp==0)
				{
					printf("ERROR\n");
					exit(1);
				}
				fwrite(tcard,sizeof(struct card),end-begin+1,fp);
				fclose(fp);	
				printf("\n\n		   注册成功！\n");
				judge=2;
			}
			else
			{
				printf("\n		*  部分数据已存在，无法注册！\n");
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
		printf("\n		这里是删除校园卡界面！\n");
		printf("		--------------------------------------------------\n");
		printf("		**************************************************\n");
		printf("		*                                                *\n");
		printf("		*  请输入入学年份：                   (2001-2099)*\n");
		printf("		*                                                *\n");
		printf("		*  请输入所在学院代号：              （01-11）   *\n");
		printf("		*                                                *\n");
		printf("		*  请输入所在班级：                  （01-20）   *\n"); 
		printf("		*                                                *\n");
		printf("		*  请输入起始学号：                  （01-99）   *\n");
		printf("		*                                                *\n");
		printf("		*  请输入终止学号：                  （01-99）   *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*                                                *\n");
		printf("		*  注：输入0则返回上一界面                       *\n");
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
				printf("\n\n\n\n\n\n\n\n\n		*  年份错误！\n");
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
				printf("\n\n\n\n\n\n\n\n		*  学院代号不存在！\n");
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
				printf("\n\n\n\n\n\n		*  班级错误！\n");
				Sleep(2000);
				continue; 
			}
			goto_xy(35,11);
			scanf("%d",&begin);
			if (begin<=0 || begin>=100) 
			{
				printf("\n\n\n\n		*  起始学号错误！\n");
				Sleep(2000);
				continue;
			}
			goto_xy(35,13);
			scanf("%d",&end);
			if (end<=0 || end>=100) 
			{
				printf("\n\n		*  终止学号错误！\n");
				Sleep(2000);
				continue;
			}
			if (end<begin) 
			{
				printf("\n		*  终止学号不能小于起始学号！\n");
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
					sprintf(s,"%s%s.dat","信息\\",s);
					remove(s);	
				}
				else
				{
					sign=0;
					printf("\n		*  部分数据不存在，无法删除！\n");
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
				printf("\n		*  删除成功！\n");
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
//	saveData();	//存入上网记录等数据 
	int key;	//登陆后，存放卡号在数组中的位置 
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
					}//小于0表示登陆失败 
					else
					{
						Sleep(2000);
						system("cls");
						do 
						{
							menu(key);	//登陆成功后进入主菜单 
							int choice; 
							int judge=0;//挂失或修改密码后重新登陆 
							printf("\n		请输入你的选择：");
							scanf("%d",&choice);
							system("cls");
							int flag;
							int i; 
							switch (choice)
							{
								case 0:break;	//选择0表示退出登陆 
								case 1:	
										do
										{
											refermenu(key);	//选择1进入查询菜单 
											flag=runrefer(key);	//根据查询菜单的选择结果运行 
											system("cls");
										} while (flag);
										break;
								case 2:	if (recharge(key))
										{
											Sleep(2000);
											system("cls");
										}
										else system("cls");	
										break;	//选择2进入充值界面 
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
	printf("		*  失物招领小黑板                        *\n");
	int i;
	int k=0;
	for (i=cnt-1;i>=0;i--)
	{
		if (k>=3) break;
		k++;
		printf("		*  %d、%s  请失主联系 %11s  *\n",k,r[i].ID,r[i].tel);
	} 
	if (k==0) printf("		*  暂无信息                              *\n");
	printf("		******************************************\n");
	printf("		------------------------------------------\n");
}

void selectstatus()
{
	printf("		******************************************\n");
	printf("		*           请选择功能：                 *\n");
	printf("		*           1、管理员登陆                *\n");
	printf("		*           2、学生登陆                  *\n");
	printf("		*           3、自助补卡                  *\n");
	printf("		*           4、挂失与解除挂失            *\n");
	printf("		*           5、忘记密码                  *\n");
	printf("		******************************************\n\n");
}

int runselect()
{
	int choice=0;
	printf("\n		请输入你的选择：");
	scanf("%d",&choice);
	return choice;
}

int Adrlogin()
{
	int judge=0;
	char id[10];
	char pass[20];
	int i;
	printf("\n		请输入账号：");
	scanf("%10s",id);
	printf("\n		请输入密码：");
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
	if (strcmp(id,Adr.ID)) printf("\n		账号不存在！\n\n");
	else
	{
		if (strcmp(pass,Adr.password)) printf("\n		密码错误！\n\n");
		else 
		{
			judge=1;
			printf("\n		登陆成功！\n\n");
		}
	}	
	return judge;	
}

void Adrmenu()
{
	printf("\n		您是管理员！\n");
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*      请选择功能：          *\n");
	printf("		*      1、注册校园卡         *\n");
	printf("		*      2、删除校园卡         *\n");
	printf("		*      3、查询已有校园卡     *\n");
	printf("		*      0、退出               *\n");
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
		printf("\n		这里是解冻界面！\n");
		printf("		----------------------------\n");
		printf("		****************************\n");
		printf("		*  目前已挂失的校园卡：    *\n");
		int j;
		int k=0;
		for (j=0;j<count;j++)
		{
			if (Card[j].state) printf("		* %2d、%s  %-10s*\n",++k,Card[j].ID,Card[j].name);
		} 
		if (k==0) printf("		*             无           *\n");
		printf("		****************************\n");
		printf("\n		--------------------------------------------\n");
		printf("\n		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  请输入要解除冻结的校园卡号：            *\n");
		printf("		*                                          *\n");
		printf("		*  请输入密码：                            *\n");
		printf("		*                                          *\n");
	    printf("		*                                          *\n");
	    printf("		*                                          *\n");
	    printf("		*                                          *\n");
		printf("		*  注：输入0则返回上一个界面               *\n");
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
				printf("\n		*  该账户不存在！\n\n");
				Sleep(2000);
				system("cls");
			}
			else if (strcmp(pass,Card[i].password)==0)
			{
				if (Card[i].state==0)
				{
					printf("\n		*  该账户未挂失！\n\n");
					Sleep(2000);
					system("cls");
				} 
				else
				{
					Card[i].state=0;
					printf("\n		*  解除冻结成功！\n\n");
					sign=2;
					saveCardData(count);
					Sleep(2000);
					system("cls");
				}
			}
			else
			{
				printf("\n		*  密码错误！\n\n");
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
	printf("\n		请输入账号：");
	scanf("%10s",id);
	printf("\n		请输入密码：");
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
					printf("\n		登陆成功！\n\n");
				}
				else printf("\n		您的账户已冻结！\n\n");
				break;
			} 
			else 
			{
				printf("\n		密码错误！\n");
				cnt[i]++;
				switch (cnt[i])
				{
					case 1:printf("\n		您还有2次输入机会！\n\n");break;
					case 2:printf("\n		您还有1次输入机会！\n\n");break;
					default:break;
				}
				if (cnt[i]>=3) 
				{
					Card[i].state=1;
					saveCardData(count);
					printf("\n		您的账户已冻结！\n\n");break;
					cnt[i]=0;
				}
			}
		}
	if (judge==0) printf("\n		账号不存在！\n\n");
	return k;
}

void menu(int n)
{
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*    请选择功能：            *\n");
	printf("		*    1、查询                 *\n");
	printf("		*    2、充值                 *\n");
	printf("		*    3、重置密码             *\n");
	printf("		*    4、登记失物招领信息     *\n");
	printf("		*    5、删除失物招领信息     *\n");	
	printf("		*    0、退出                 *\n");
	printf("		******************************\n\n");
}

void refermenu(int n)
{
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		------------------------------\n");
	printf("		******************************\n");
	printf("		*       请选择功能：         *\n");
	printf("		*       1、查询余额          *\n");
	printf("		*       2、查询上网记录      *\n");
	printf("		*       3、查询上网总时长    *\n");
	printf("		*       4、查询上网总费用    *\n");
	printf("		*       5、查询借阅记录      *\n");
	printf("		*       0、返回              *\n");
	printf("		******************************\n\n");
}


int recharge(int n)
{	
	int amount;
	do
	{
		printf("\n		您的卡号为：%s\n",Card[n].ID);
		printf("		----------------------------\n");
		printf("\n		请输入充值金额："); 
		printf("\n\n\n\n		注：输入0则返回上一界面！\n");
		goto_xy(32,4);
		scanf("%d",&amount);
		if (amount>0 && amount<=500) 
		{
			Card[n].remain+=amount*1.0;
			saveCardData(count);
			printf("\n		充值成功！\n\n");
			Sleep(2000);
			system("cls");
			printf("\n		您的卡号为：%s\n",Card[n].ID);
			printf("		----------------------------\n");
			printf("		您目前的余额为：%.2f\n\n",Card[n].remain);
			int i;
			for (i=5;i>0;i--)
			{ 
				printf("		系统将在%d秒后为您返回上一个界面\r",i);
				Sleep(1000);
			}
		}
		else if (amount==0) break;
		else
		{
			printf("\n		请重新输入金额！\n\n");
			Sleep(2000);
			system("cls");
		}
	} while (amount<0);
	return amount;
} 

int runrefer(int n)
{
	int choice;
	printf("\n		请输入你的选择：");
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
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		您的余额为：%.2f\n",Card[n].remain); 
	printf("		----------------------------\n\n");
	printf("\n		注：按回车键返回！\n");
	printf("		");
	getchar(); 
	getchar();
}

void referWeb(int n)
{
	system("cls");
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		----------------------------\n");
	struct record r[3];
	char s[50];
	sprintf(s,"%s%s.dat","信息\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),3,fp);
	printf("\n		您的上网记录为：\n");
	int i;
	int judge=1;
	printf("\n		上网日期    开始时间  上网时长  上网地点  本次上网费用\n");
	for (i=0;i<cnt;i++)
	{
		judge=0;
		printf("\n		%s  %s  %d(分)     %s    %.2f（元）\n",r[i].date,r[i].start_time,r[i].duration,r[i].place,r[i].duration*0.2/60);
	}
	if (judge) printf("\n		暂无记录！\n");
	fclose(fp);
	printf("\n\n		注：按回车键返回！\n");
	getchar();
	getchar();
}

void referbook(int n)
{
	system("cls");
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		----------------------------\n");
	struct record r[3];
	char s[50];
	sprintf(s,"%s%s.dat","信息\\",Card[n].ID);
	FILE* fp=fopen(s,"rb");
	if (fp==0) 
	{
		printf("ERROR\n");
		exit(1);
	}
	int cnt=fread(r,sizeof(struct record),3,fp);
	printf("\n		您的借阅记录为：\n");
	int i;
	int judge=1;
	printf("\n		借书日期       所借书名     还书截止日期\n");
	for (i=0;i<cnt;i++)
	{
		judge=0;
		printf("\n		%s    %-12s%14s\n",r[i].Book.when,r[i].Book.bookname,r[i].Book.deadline);
	}
	if (judge) printf("\n		暂无记录！\n");
	fclose(fp);
	printf("\n\n		注：按回车键返回！\n");
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
		printf("\n		这里是挂失与解除挂失界面！\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  请输入需要挂失的校园卡号：         *\n");
		printf("		*                                     *\n");
		printf("		*  请输入密码：                       *\n");	
		printf("		*                                     *\n"); 
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*  注：输入0则返回上一界面            *\n");
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
						printf("\n		*  挂失成功！\n\n");
						sign=0;
						Sleep(2000);
						system("cls");
					}
					else 
					{
						printf("\n		*  您的账户已挂失！\n\n");
						Sleep(2000);
						system("cls");
					}
					break;
				} 
				else 
				{
					printf("\n		*  密码错误！\n\n");
					Sleep(2000);
					system("cls");
				}
			}
		if (judge==0) 
		{
			printf("\n		*  账号不存在！\n\n");
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
		printf("\n		这里是重置密码界面！\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  请输入新密码：                     *\n");
		printf("		*                                     *\n");
		printf("		*  请再次输入新密码：                 *\n");
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
			printf("\n		*  两次输入不一致，请重新输入！\n\n");
			Sleep(2000);
			system("cls"); 
		}
	} while (strcmp(newpass,newpass1));
	strcpy(Card[n].password,newpass);
	saveCardData(count);
	printf("\n		*  重置密码成功！\n\n");
}

void AutoMakeCard()
{
	int sign=1;
	do
	{
		printf("\n		这里是自助补卡终端！\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  请输入需要补办的校园卡号：              *\n");
		printf("		*                                          *\n");
		printf("		*  请输入密码：                            *\n");
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
		printf("		*  注：输入0则返回上一个界面               *\n");
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
			printf("\n		*  账户不存在！\n\n");
			Sleep(2000);
			system("cls");
			continue;
		}
		else if (strcmp(pass,Card[i].password)) 
		{
			printf("\n		*  密码错误！\n\n");
			Sleep(2000);
			system("cls");
			continue;
		}
		else 
		{
			sign=0;
			printf("\n		*  请稍候！\n");
			int j;
			for (j=5;j>0;j--)
			{	
				Sleep(2000);
				printf("		*  %d\n",j);
			}
			Card[i].state=0;
			Card[i].remain-=25.0;
			saveCardData(count);
			printf("\n		*  出卡成功！\n\n");
			Sleep(2000);
		} 
	} while (sign);
	
}

int freezemenu()
{
	int judge=1;
	printf("\n		这里是挂失与解除挂失界面！\n");
	printf("		--------------------------------------\n");
	printf("		**************************************\n");
	printf("		*                                    *\n");
	printf("		*        请选择功能：                *\n");
	printf("		*        1、挂失                     *\n");
	printf("		*        2、解除挂失                 *\n"); 
	printf("		*        0、返回                     *\n");
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
		printf("\n		这里是找回密码界面！\n");
		printf("		---------------------------------------\n");
		printf("		***************************************\n");
		printf("		*                                     *\n");
		printf("		*  请输入校园卡号：                   *\n");
		printf("		*                                     *\n");
		printf("		*  请输入姓名：                       *\n");
		printf("		*                                     *\n");
		printf("		*  请输入身份证后4位：                *\n"); 
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*                                     *\n");
		printf("		*  注：输入0则返回上一界面            *\n");
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
					printf("\n		*  信息验证成功！\n");
					Sleep(2000);
					system("cls");
					reset(i);
					break;
				}
				else
				{
					printf("\n		*  信息错误！\n");
					Sleep(2000);
					system("cls");
				}
			}
			else
			{
				printf("\n		*  账号不存在！\n");
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
		printf("\n		这里是失物招领界面！\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  请输入你捡到的校园卡号：                *\n");
		printf("		*                                          *\n");
		printf("		*  请输入你的电话号码：                    *\n");
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
		printf("		*  注：输入0则返回上一个界面               *\n");
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
				printf("\n		*  请输入正确的电话号码！\n");
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
				FILE *fp=fopen("信息\\失物招领信息.dat","ab+");
				if (fp==0)
				{
					printf("ERROR\n");
					exit(1);	
				}
				fwrite(&r,sizeof(struct lostinformation),1,fp);
				fclose(fp);
				printf("\n		*  登记成功！\n");
				Sleep(2000);
			}
			else if (flag==0)
			{
				printf("\n		*  该卡号不存在！\n");
				Sleep(2000); 
			}
			else 
			{
				printf("\n		*  该卡号已在失物招领信息中！\n");
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
		printf("\n		这里是删除失物招领信息界面！\n");
		printf("		--------------------------------------------\n");
		printf("		********************************************\n");
		printf("		*                                          *\n");
		printf("		*  请输入校园卡号：                        *\n");
		printf("		*                                          *\n");
		printf("		*  请输入密码：                            *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*                                          *\n");
		printf("		*  注：输入0则返回上一个界面               *\n");
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
				FILE *fp=fopen("信息\\失物招领信息.dat","rb");
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
					fp=fopen("信息\\失物招领信息.dat","wb+");
					if (fp==0)
					{
						printf("ERROR\n");
						exit(1);	
					}
					fwrite(Lostinformation,sizeof(struct lostinformation),cnt-1,fp);
					fclose(fp);
					printf("\n		*  删除成功！\n");
					sign=0;
					Sleep(2000);
				}
				else
				{
					printf("\n		*  您的校园卡不在失物招领信息中！\n");
					Sleep(2000);
					continue;
				} 
			}
			else
			{
				printf("\n		*  密码错误！\n");
				Sleep(2000);
				continue;
			}
		}
		else
		{
			printf("\n		*  账号不存在！\n");
			Sleep(2000);
			continue;	
		} 
	} while (sign); 
}

void referAllCard()
{
	system("cls");
	printf("\n		您是管理员！\n");
	printf("		---------------------------------------\n");
	printf("		***************************************\n");
	printf("		*                                     *\n");
	printf("		*  目前已注册的校园卡：               *\n");
	int i;
	for (i=0;i<count;i++)
	{
		printf("		* %2d、%s  %-21s*\n",i+1,Card[i].ID,Card[i].name);
	} 
	printf("		*                                     *\n");
	printf("		*  注：按回车键返回！                 *\n");
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
	sprintf(s,"%s%s.dat","信息\\",Card[n].ID);
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
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		您的上网总时长为：%d（分）\n",sum); 
	printf("		----------------------------\n\n");
	printf("\n		注：按回车键返回！\n");
	printf("		");
	getchar(); 
	getchar();
} 

void referAllCost(int n)
{
	struct record r[size];
	char s[50];
	sprintf(s,"%s%s.dat","信息\\",Card[n].ID);
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
	printf("\n		您的卡号为：%s\n",Card[n].ID);
	printf("		----------------------------\n");
	printf("		您的上网总费用为：%.2f（元）\n",sum); 
	printf("		----------------------------\n\n");
	printf("\n		注：按回车键返回！\n");
	printf("		");
	getchar(); 
	getchar();
} 
