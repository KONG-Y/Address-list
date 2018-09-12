#ifndef _TONGXUN_H_
#define _TONGXUN_H_
#define SIZEMAX 1000

struct Person
{
	char m_strName[SIZEMAX];    //姓名
	char m_strWork[SIZEMAX];    //职务
	char m_strWorkName[SIZEMAX];//职称
	char m_strEmall[SIZEMAX];   //电子邮箱
	char m_strPhone[SIZEMAX];   //手机号
	struct Person *m_pNext; //下一成员
};

enum Element :char
{
	e_cName = '1',
	e_cWork = '2',
	e_cWorkName = '3',
	e_cEmall = '4',
	e_cPhone = '5',
};

Person *Read(Person *pHead);
Person *LastPerson(Person *pHead, Person *pCurrent);
Person *Get(Person *pHead, Element element, char str_val[]);
Person *Delete(Person *pHead);
Person *Sort(Person *pHead);
int Size(Person *pHead);
void CleanString(char str_val[]);
void Put(Person *pHead);
void Foreach(Person *pHead);
void Exchange(Person *pHead, Person *pOne, Person *pTwo);
void Correct(Person *pHead);
void MenuFind(Person *pHead);
void Menu(Person *pHead);
void Save(Person *pHead);

#endif
