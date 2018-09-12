/*****************************************************************************

*问题描述：通讯录管理程序，功能实现：添加，删除，修改，显示，分类查找，排序

*****************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include"tongxun.h"
#define SIZEMAX 1000

int main()
{
	Person *p = (Person*)malloc(sizeof(Person));
	p = Read(p);
	Menu(p);
	return 0;

}

/*加载通讯录信息*/
Person *Read(Person *pHead)
{
	Person *pCurrent;     //当前成员结点
	FILE *fp;             //文本数据
	char str_buf[SIZEMAX];//读取的文本字符串数据
	char str_val[SIZEMAX];//读取的属性字符串数据
	int n_number;         //属性编号
	int n_mark;           //文件字符串位置
	int n_mark2;          //属性存储字符串位置
	int n_flag;           //字符有的标志

	pCurrent = pHead;     //当前结点为首结点

						  //打开文本字符串数据，且判断是否空 
	if ((fp = fopen("data.txt", "r")) == NULL)
	{
		printf("文件找不到\n");
		exit(1);
	}

	//当文本数据不为空时，读取文本字符串数据
	while (fgets(str_buf, SIZEMAX, fp) != NULL)
	{
		//防止文件字符串第一个为回车键或者为空或者为结束符
		if ((str_buf[0] != '\n') && (str_buf[0] != ' ') && (str_buf[0] != '\0'))
		{
			Person *pNew = (Person*)malloc(sizeof(Person));

			n_mark = 0;  //初始化文本数据位置为0
			n_number = 1;//初始化属性编号为1

						 //为5个属性赋值
			while (n_number <= 5)
			{
				n_mark2 = 0;//属性字符串位置初始化

							//逐个属性赋值
				while ((str_buf[n_mark] != ' ') && (str_buf[n_mark] != '\n'))
				{
					str_val[n_mark2] = str_buf[n_mark];//把文本当前字符赋值到属性字符串中
					n_mark++;                          //文本数据当前位置到下一位
					n_mark2++;                         //属性字符串当前位置到下一位
					n_flag = 1;                        //字符不为空或'\n',则为1
				}

				//属性字符串赋结束符
				if ((str_buf[n_mark] == ' ') && (n_flag == 1) || (str_buf[n_mark] == '\n') && (n_flag == 1))
				{
					str_val[n_mark2] = '\0';//为字符串赋结束字符

											//属性赋值
					switch (n_number)
					{

					case 1:
						strcpy(pNew->m_strName, str_val);//姓名赋值
						break;


					case 2:
						strcpy(pNew->m_strWork, str_val);//职务赋值
						break;


					case 3:
						strcpy(pNew->m_strWorkName, str_val);//职称赋值
						break;


					case 4:
						strcpy(pNew->m_strPhone, str_val);//手机赋值
						break;


					case 5:
						strcpy(pNew->m_strEmall, str_val);//邮箱赋值

						pNew->m_pNext = NULL;             //新结点的下一结点为空
						pCurrent->m_pNext = pNew;         //当前结点的下一结点为新结点
						pCurrent = pCurrent->m_pNext;     //当前结点移动到下一结点（新结点）
						break;
					}

					n_number++;                           //属性编号到下一位
					n_flag = 0;                           //当前不能继续赋结束符
					CleanString(str_val);         //清理属性字符串，以便存储下一个属性字符串
				}

				n_mark++;//文本数据当前位置到下一位
			}
		}
	}

	return pHead;
}

/*保存通讯录*/
void Save(Person *pHead)
{
	char c_flag;
	FILE *fp;
	Person *pCurrent;

	c_flag = '\0';              //返回菜单判断初始化为结束符
	pCurrent = pHead->m_pNext;  //当前结点为首结点的下一结点（首结点为空）
	fp = fopen("save.txt", "w");//打开保存文件

	while (pCurrent != NULL)
	{
		/*保存属性数据到文件*/
		fprintf(fp, "%s\t", pCurrent->m_strName);
		fprintf(fp, "%s\t", pCurrent->m_strWork);
		fprintf(fp, "%s\t", pCurrent->m_strWorkName);
		fprintf(fp, "%s\t", pCurrent->m_strPhone);
		fprintf(fp, "%s\n", pCurrent->m_strEmall);

		pCurrent = pCurrent->m_pNext;//当前结点移动到下一结点
	}

	printf("保存成功！\n");
	printf("按任意键返回菜单\n");
	scanf("%c", &c_flag);

	//返回菜单
	if (c_flag != '\0')
	{
		system("cls");
		Menu(pHead);
	}

}

/*字符串初始化为空*/
void CleanString(char str_val[])
{
	char str_null[] = { "" };

	strcpy(str_val, str_null);
}


/*链表大小*/
int Size(Person *pHead)
{
	int i;

	//遍历到结点的下一结点为空
	for (i = 0; pHead->m_pNext != NULL; i++)
	{
		pHead = pHead->m_pNext;//当前结点移动到下一结点
	}

	return i;//返回链表结点的数量
}

/*访问当前成员的上一成员*/
Person *LastPerson(Person *pHead, Person *pFind)
{
	Person *pLast;//存储当前结点的上一结点

	pLast = pHead;//从首结点开始

				  //如果上结点的下一结点（当前结点）为空，返回空
	if (pLast->m_pNext == NULL)
	{
		return NULL;
	}

	//如果上结点的下一结点不为查找的结点
	if (pLast->m_pNext != pFind)
	{
		pLast = LastPerson(pLast->m_pNext, pFind);//从下一结点递归函数
	}
	else
	{
		return pLast;//找到查找的结点，返回上结点
	}

}

/*添加*/
void Put(Person *pHead)
{
	char str_name[SIZEMAX];    //姓名字符串
	char str_work[SIZEMAX];    //职务字符串
	char str_workName[SIZEMAX];//职称字符串
	char str_emall[SIZEMAX];   //邮箱字符串
	char str_phone[SIZEMAX];   //手机字符串
	char c_flag;               //循环判断
	char c_flag2;              //循环判断
	Person *pCurrent;          //当前结点

	c_flag = '1';              //循环为1，跳出循环为0
	pCurrent = pHead;          //当前成员为第一名成员

	printf("请输入联系人的姓名\n");
	scanf("%s", str_name);
	printf("请输入联系人的职务\n");
	scanf("%s", str_work);
	printf("请输入联系人的职称\n");
	scanf("%s", str_workName);
	printf("请输入联系人的邮箱\n");
	scanf("%s", str_emall);
	printf("请输入联系人的手机\n");
	scanf("%s", str_phone);
	getchar();

	while (c_flag == '1')
	{
		//当前结点的下一结点为空，则在下一结点新建结点
		if (pCurrent->m_pNext == NULL)
		{
			Person *pNew;//新结点
			pNew = (Person*)malloc(sizeof(Person));//为新结点申请内存块

			strcpy(pNew->m_strEmall, str_emall);
			strcpy(pNew->m_strName, str_name);
			strcpy(pNew->m_strWork, str_work);
			strcpy(pNew->m_strPhone, str_phone);
			strcpy(pNew->m_strWorkName, str_workName);

			pNew->m_pNext = NULL;    //新结点的下一结点为空
			pCurrent->m_pNext = pNew;//当前结点的下一结点为新结点
			c_flag = '0';            //跳出循环

			printf("添加成功！\n");
			printf("继续添加按“1”\t返回菜单按“2”\n");
		}
		else
		{
			pCurrent = pCurrent->m_pNext;//当前成员变为下一个成员
		}
	}

	while (c_flag == '0')
	{
		scanf("%c", &c_flag2);
		getchar();

		//继续添加
		if (c_flag2 == '1')
		{
			c_flag = '1';
			system("cls");
			Put(pHead);
		}
		//返回菜单
		else if (c_flag2 == '2')
		{
			c_flag = '1';
			system("cls");
			Menu(pHead);
		}
		//无效输入
		else
		{
			printf("无效数字，请重新输入\n");
		}

	}
}

/*查找*/
Person *Get(Person *pHead, Element element, char str_value[])
{
	int n_flag;      //循环判断
	Person *pCurrent;//当前结点

	n_flag = 1;               //循环为1，跳出循环为0
	pCurrent = pHead->m_pNext;//当前结点为首结点的下一结点（首结点为空）

	while (n_flag == 1)
	{
		//当前结点为空
		if (pCurrent == NULL)
		{
			n_flag = 0; //跳出循环
			return NULL;//返回空值
		}

		switch (element)
		{
			//姓名查询
		case e_cName:

			//不符合条件，换下一结点
			if (strcmp(pCurrent->m_strName, str_value) != 0)
			{
				pCurrent = pCurrent->m_pNext;
			}
			//符合条件，返回当前结点
			else
			{
				n_flag = 0;
				return pCurrent;
			}

			break;

			//职务查询
		case e_cWork:

			//不符合条件，换下一结点
			if (strcmp(pCurrent->m_strWork, str_value) != 0)
			{
				pCurrent = pCurrent->m_pNext;
			}
			//符合条件，返回当前结点
			else
			{
				n_flag = 0;
				return pCurrent;
			}

			break;

			//职称查询
		case e_cWorkName:

			//不符合条件，换下一结点
			if (strcmp(pCurrent->m_strWorkName, str_value) != 0)
			{
				pCurrent = pCurrent->m_pNext;
			}
			//符合条件，返回当前结点
			else
			{
				n_flag = 0;
				return pCurrent;
			}

			break;

			//手机查询
		case e_cPhone:

			//不符合条件，换下一结点
			if (strcmp(pCurrent->m_strPhone, str_value) != 0)
			{
				pCurrent = pCurrent->m_pNext;
			}
			//符合条件，返回当前结点
			else
			{
				n_flag = 0;
				return pCurrent;
			}

			break;

			//邮箱查询
		case e_cEmall:

			//不符合条件，换下一结点
			if (strcmp(pCurrent->m_strEmall, str_value) != 0)
			{
				pCurrent = pCurrent->m_pNext;
			}
			//符合条件
			else
			{
				CleanString(str_value);//清空查找所要检索的关键字
				n_flag = 0;            //跳出循环
				return pCurrent;       //返回当前结点
			}

			break;

		default:
			printf("无效数字，请重新输入\n");
			break;

		}
	}
}

/*遍历通讯录*/
void Foreach(Person *pHead)
{
	char c_flag;              //循环判断
	char c_flag2;             //返回菜单判断
	Person *pCurrent;         //当前结点

	c_flag = '1';             //循环为1，跳出循环为0
	c_flag2 = '\0';           //按键判断
	pCurrent = pHead->m_pNext;//当前结点为首结点的下一结点（首结点为空）

	while (c_flag == '1')
	{
		//当前结点不为空，则输出信息
		if (pCurrent != NULL)
		{
			printf("姓名:%s\n", pCurrent->m_strName);
			printf("职务:%s\n", pCurrent->m_strWork);
			printf("职称:%s\n", pCurrent->m_strWorkName);
			printf("手机:%s\n", pCurrent->m_strPhone);
			printf("邮箱:%s\n", pCurrent->m_strEmall);
			printf("\n");

			pCurrent = pCurrent->m_pNext;//当前结点移动到下一结点
		}
		//当前结点为空，则跳出循环
		else
		{
			c_flag = '0';
		}

	}

	printf("按任意键返回菜单按\n");
	scanf("%c", &c_flag2);

	//返回菜单
	if (c_flag2 != '\0')
	{
		system("cls");
		Menu(pHead);
	}

}

/*删除*/
Person *Delete(Person *pHead)
{
	Person *pCurrent;   //当前结点
	Person *pLast;      //上结点
	Element element;    //属性
	char str_value[100];//属性查找字符串
	char c_flag;        //循环判断

	c_flag = '0';       //循环为0，跳出循环为1

	printf("请选择所要查找联系人的方式，按对应的编号\n");
	printf("1.姓名\t2.职务\t3.职称\t4.邮箱\t5.手机\n");
	scanf("%c", &element);
	getchar();
	printf("请输入所要删除的联系人的查找信息\n");
	scanf("%s", str_value);
	getchar();

	pCurrent = Get(pHead, element, str_value);//查找结点
	CleanString(str_value);                   //清除属性查找字符串

											  //找不到所要删除的结点
	if (pCurrent == NULL)
	{
		printf("通讯录没有此联系人,无法执行删除操作\n");

	}
	//找到所要删除的结点
	else
	{
		pLast = LastPerson(pHead, pCurrent);//访问删除结点的上一结点
		pLast->m_pNext = pCurrent->m_pNext; //（上一结点的下一结点）变为（删除结点的下一结点）
		free(pCurrent);                     //释放内存
		printf("删除成功！\n");
	}

	while (c_flag == '0')
	{
		printf("继续删除按“1”\t返回菜单按“2”");
		scanf("%c", &c_flag);
		getchar();

		//继续删除
		if (c_flag == '1')
		{
			system("cls");
			pHead = Delete(pHead);
		}
		//返回菜单 
		else if (c_flag == '2')
		{
			system("cls");
			Menu(pHead);
		}
		//无效输入
		else
		{
			printf("无效数字，请重新输入\n");
			system("cls");
		}

	}

	return pHead;//返回链表的首结点
}

/*交换*/
void Exchange(Person *pHead, Person *pOne, Person *pTwo)
{
	Person *pTemp;

	pTemp = (Person*)malloc(sizeof(Person));

	/*中间结点属性赋值*/
	strcpy(pTemp->m_strName, pOne->m_strName);
	strcpy(pTemp->m_strEmall, pOne->m_strEmall);
	strcpy(pTemp->m_strPhone, pOne->m_strPhone);
	strcpy(pTemp->m_strWork, pOne->m_strWork);
	strcpy(pTemp->m_strWorkName, pOne->m_strWorkName);

	/*第一个结点属性交换*/
	strcpy(pOne->m_strName, pTwo->m_strName);
	strcpy(pOne->m_strEmall, pTwo->m_strEmall);
	strcpy(pOne->m_strPhone, pTwo->m_strPhone);
	strcpy(pOne->m_strWork, pTwo->m_strWork);
	strcpy(pOne->m_strWorkName, pTwo->m_strWorkName);

	/*第二个结点属性交换*/
	strcpy(pTwo->m_strName, pTemp->m_strName);
	strcpy(pTwo->m_strEmall, pTemp->m_strEmall);
	strcpy(pTwo->m_strPhone, pTemp->m_strPhone);
	strcpy(pTwo->m_strWork, pTemp->m_strWork);
	strcpy(pTwo->m_strWorkName, pTemp->m_strWorkName);

}

/*排序*/
Person *Sort(Person *pHead)
{
	int n_size;     //链表大小
	Person *pFirst; //第一结点
	Person *pSecond;//第二结点
	Person *pTemp;

	pTemp = (Person*)malloc(sizeof(Person));
	pFirst = pHead->m_pNext; //第一个结点为首结点的下一结点（首结点为空）
	n_size = Size(pHead);    //获取链表大小

							 /*选择排序*/
	for (int i = 0; i < n_size; i++)
	{
		for (int j = i + 1; j < n_size; j++)
		{
			//从第一个结点的下一结点开始循环
			if (j == i + 1)
			{
				pSecond = pFirst->m_pNext;
			}

			//字符串比较
			if (strcmp(pFirst->m_strName, pSecond->m_strName)>0)
			{
				Exchange(pHead, pFirst, pSecond);//交换结点
			}

			//第二个结点为下一结点
			if (pSecond->m_pNext != NULL)
			{
				pSecond = pSecond->m_pNext;//第二个结点移动到下一结点
			}

		}

		//第一个结点为下一结点
		if (pFirst->m_pNext != NULL)
		{
			pFirst = pFirst->m_pNext;//第一个结点移动到下一结点
		}

	}

	return pHead;//返回链表的首结点
}

/*修改*/
void Correct(Person *pHead)
{
	char str_name[100]; //要修改的联系人姓名字符串
	char str_value[100];//修改的新属性字符串
	char c_number;      //属性编号
	char c_flag;        //循环判断
	Person *pCurrent;   //当前结点

	c_flag = '1';       //循环为1，跳出循环为0

	printf("请输入所要修改的联系人的姓名\n");
	scanf("%s", str_name);
	getchar();

	pCurrent = Get(pHead, e_cName, str_name);//查找所要修改的联系人

											 //找不到所要修改的联系人
	if (pCurrent == NULL)
	{
		printf("通讯录没有此联系人\n");
	}
	//找到所要修改的联系人
	else
	{
		while (c_flag == '1')
		{
			system("cls");
			printf("请选择修改的信息,输入对应的编号\n");
			printf("1.姓名\t2.职务\t3.职称\t4.邮箱\t5.手机\n");

			scanf("%c", &c_number);
			getchar();

			//属性修改
			switch (c_number)
			{
				//姓名修改
			case '1':
				CleanString(pCurrent->m_strName);      //成员旧信息清理
				printf("请输入新的姓名\n");
				scanf("%s", str_value);
				getchar();
				strcpy(pCurrent->m_strName, str_value);//成员新信息赋值
				printf("修改成功！\n");
				c_flag = '0';//跳出循环
				break;

				//职务修改
			case '2':
				CleanString(pCurrent->m_strWork);//成员旧信息清理
				printf("请输入新的职务\n");
				scanf("%s", str_value);
				getchar();
				strcpy(pCurrent->m_strWork, str_value);//成员新信息赋值
				printf("修改成功！\n");
				c_flag = '0';//跳出循环
				break;

				//职称修改
			case '3':
				CleanString(pCurrent->m_strWorkName);//成员旧信息清理
				printf("请输入新的职称\n");
				scanf("%s", str_value);
				getchar();
				strcpy(pCurrent->m_strWorkName, str_value);//成员新信息赋值
				printf("修改成功！\n");
				c_flag = '0';//跳出循环
				break;

				//邮箱修改
			case '4':
				CleanString(pCurrent->m_strEmall);//成员旧信息清理
				printf("请输入新的邮箱\n");
				scanf("%s", str_value);
				getchar();
				strcpy(pCurrent->m_strEmall, str_value);//成员新信息赋值
				printf("修改成功！\n");
				c_flag = '0';//跳出循环
				break;

				//手机修改
			case '5':
				CleanString(pCurrent->m_strPhone);//成员旧信息清理
				printf("请输入新的手机\n");
				scanf("%s", str_value);
				getchar();
				strcpy(pCurrent->m_strPhone, str_value);//成员新信息赋值
				printf("修改成功！\n");
				c_flag = '0';//跳出循环
				break;

			default:
				printf("无效输入，请重新输入\n");
				break;
			}

		}

	}

	while (c_flag == '0')
	{
		printf("继续修改请按“1”\t返回菜单请按“2”\n");
		scanf("%c", &c_number);
		getchar();

		//继续修改
		if (c_number == '1')
		{
			c_flag = '1';
			system("cls");
			Correct(pHead);
		}
		//返回菜单
		else if (c_number == '2')
		{
			c_flag = '1';
			system("cls");
			Menu(pHead);
		}
		//无效输入
		else
		{
			printf("无效数字，请重新输入\n");
		}

	}
}

/*菜单查找*/
void MenuFind(Person *pHead)
{
	char c_number;      //属性编号
	char str_value[100];//属性查找字符串
	char c_flag;        //循环判断
	char c_flag2;       //按键判断
	Element element;    //属性变量
	Person *pFind;      //查找结点

	c_flag = '1';       //循环为1，跳出循环为0

	printf("请选择所要查询的联系人的关键信息\n");
	printf("姓名查询请按“１”\n");
	printf("职务查询请按“２”\n");
	printf("职称查询请按“３”\n");
	printf("手机查询请按“４”\n");
	printf("邮箱查询请按“５”\n");

	while (c_flag == '1')
	{
		scanf("%c", &c_number);
		getchar();

		switch (c_number)
		{
			//姓名查询
		case '1':
			printf("请输入所要查询的姓名\n");
			element = e_cName;
			c_flag = '0';
			break;

			//职务查询
		case '2':
			printf("请输入所要查询的职务\n");
			element = e_cWork;
			c_flag = '0';
			break;

			//职称查询
		case '3':
			printf("请输入所要查询的职称\n");
			element = e_cWorkName;
			c_flag = '0';
			break;

			//手机查询
		case '4':
			printf("请输入所要查询的手机\n");
			element = e_cPhone;
			c_flag = '0';
			break;

			//邮箱查询
		case '5':
			printf("请输入所要查询的邮箱\n");
			element = e_cEmall;
			c_flag = '0';
			break;

		default:
			printf("无效数字，请重新输入\n");
			break;
		}

	}

	scanf("%s", str_value);
	getchar();

	pFind = Get(pHead, element, str_value);//获取查找的结点

	if (pFind == NULL)
	{
		printf("通讯录没有此联系人\n");
	}

	//查找的结点不为空，直到查询完整个链表
	while (pFind != NULL)
	{
		printf("姓名:%s\n", pFind->m_strName);
		printf("职务:%s\n", pFind->m_strWork);
		printf("职称:%s\n", pFind->m_strWorkName);
		printf("手机:%s\n", pFind->m_strPhone);
		printf("邮箱:%s\n", pFind->m_strEmall);
		printf("\n");

		pFind = Get(pFind, element, str_value);//在当前结点开始查找相同的结点

	}

	printf("继续查询请按＂１＂\t返回菜单请按“２”\n");

	while (c_flag == '0')
	{
		scanf("%c", &c_flag2);
		getchar();

		//继续查询
		if (c_flag2 == '1')
		{
			c_flag = '1';
			system("cls");
			MenuFind(pHead);
		}
		//返回菜单
		else if (c_flag2 == '2')
		{
			c_flag = '1';
			system("cls");
			Menu(pHead);
		}
		//无效输入
		else
		{
			printf("无效数字，请重新输入\n");
		}

	}
}

/*菜单*/
void Menu(Person *pHead)
{
	char c_value;//执行功能选择
	char c_flag; //循环判断

	c_flag = '1';//循环为1，跳出循环为0


	printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　       通讯录信息　　         ++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　　　　查询--按“１＂　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　　　　添加--按“２＂　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　　　　删除--按“３＂　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　　　　修改--按“４”　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　遍历通讯录--按“５＂　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++　　排序通讯录--按“６＂　　　　　++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++    保存通讯录--按“7 ”          ++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++          退出--按“8 ”          ++++++++++++++++++++\n");
	printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	while (c_flag != '0')
	{
		scanf("%c", &c_value);
		getchar();
		system("cls");

		switch (c_value)
		{
		//查询
		case '1':
			c_flag = '0';
			MenuFind(pHead);
			break;

		//添加
		case '2':
			c_flag = '0';
			Put(pHead);
			break;

		//删除
		case '3':
			c_flag = '0';
			pHead = Delete(pHead);
			break;

		//修改
		case '4':
			c_flag = '0';
			Correct(pHead);
			break;

		//显示
		case '5':
			c_flag = '0';
			Foreach(pHead);
			break;

		//排序
		case '6':
			c_flag = '0';
			pHead = Sort(pHead);
			Foreach(pHead);
			break;

		//保存
		case '7':
			c_flag = '0';
			Save(pHead);
			break;

		//离开
		case '8':
			exit(1);
			break;

		default:
			printf("无效数字，按“0”返回菜单\n");
			scanf("%c", &c_flag);
			getchar();

			if (c_flag == '0')
			{
				system("cls");
				Menu(pHead);
			}

			break;
		}

	}
}


