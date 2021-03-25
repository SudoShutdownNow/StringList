#include <iostream>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;
#define MAX_WORD_LENGTH 20
#define OK 1
#define ERROR -1

struct WordNode {
	char word[MAX_WORD_LENGTH];
	WordNode* next;
	bool isEmpty;
	bool labeled;
	WordNode() :next(NULL), isEmpty(true),labeled(false) {};
	WordNode(char* myword):isEmpty(false),next(NULL),labeled(false) {
		strcpy(word, myword);
	}
	WordNode(char* myword,WordNode* mynext) :isEmpty(false),next(mynext),labeled(false) {
		strcpy(word, myword);
	}
};

int append(WordNode*& list,char* myword)//在词表后追加一个单词
{
	WordNode* newnode = new WordNode(myword);//先创建一个链表节点

	WordNode* p = list;
	if (p->isEmpty == true)//如果链表是空的
	{
		list = newnode;//把头节点设置为新创建的有内容的节点
		return OK;
	}

	for (p = list; p->next != NULL; p = p->next)//把指针移动到列表末尾
	{

	}
	p->next = newnode;//把新节点追加在末尾
	return OK;
}

int getWordFromFile(char* filename,WordNode*& list)//从文件读取单词
{
	FILE* fp = fopen(filename, "r");//打开文件

	if (fp == NULL)//判断文件是否打开成功
	{
		return ERROR;
	}

	char newword[MAX_WORD_LENGTH];
	while (fscanf(fp, "%s", &newword) != EOF)//从头读取文件直到文件尾
	{
		append(list, newword);//将读取到的单词追加在链表末尾
	}
	append(list, newword);
	return OK;
}

int getWordFromInput(WordNode*& list)//从键盘读取单词
{
	char newword[MAX_WORD_LENGTH];
	while (cin>>newword)//从头读取文件直到文件尾
	{
		if (strcmp(newword, "`") == 0)
		{
			return OK;
		}
		append(list, newword);//将读取到的单词追加在链表末尾
	}
	//append(list, newword);
	return OK;
}

int explore(WordNode* List)
{
	for (WordNode* p = List; p->next != NULL; p = p->next)
	{
		if (p->labeled == true)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//把控制台设置成红色
			//cout << "***";
			cout << p->word <<" ";

		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
				FOREGROUND_GREEN | FOREGROUND_BLUE);//控制台设置为白色
			cout << p->word << " ";
		}

	}
	return OK;
}

int seek(WordNode* paper, WordNode* target)
{
	WordNode* piter, * titer;
	titer = target;
	WordNode* label = NULL;
	for (piter = paper; piter->next != NULL; piter = piter->next)//piter从第一个单词开始遍历Paper
	{
		if (strcmp(titer->word, piter->word) == 0)//暂存相同部分开始的位置
		{
			label = piter;
		}
		while (strcmp(titer->word, piter->word) == 0)
		{
			if (titer->next == NULL)//一直匹配到目标串的末尾了，说明匹配中了
			{
				WordNode* oper = label;
				for (oper = label; oper != piter; oper = oper->next)//oper在paper上从label位置开始，直到当前位置结束
				{
					cout << oper->word << endl;
					oper->labeled = true;//将标记改为存在
				}
				oper->labeled = true;//同理把最后一个处理掉

				titer = target;//给titer归位
				//return OK;
			}

			if (piter->next != NULL)
			{
				//如果目标串没有到头，目标串和文本串指针同时向前移动
				titer = titer->next;
				piter = piter->next;
			}
			else
			{
				return OK;
			}
			
		}
	}
	return OK;
}

void testmain()
{
	char filename[20];
	cout << "请输入文本地址：";
	cin >> filename;
	cout << "请输入要查找的串：";
	WordNode* target = new WordNode;
	getWordFromInput(target);
	WordNode* paper = new WordNode;
	getWordFromFile(filename, paper);
	seek(paper, target);
	explore(paper);
	system("pause");

}

void testmain1()
{
	WordNode* input = new WordNode;
	getWordFromInput(input);
}

void main()
{
	testmain();
}
