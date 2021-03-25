#include <iostream>
#pragma warning(disable : 4996)
using namespace std;
#define MAX_WORD_LENGTH 20
#define OK 1
#define ERROR -1

struct WordNode {
	char word[MAX_WORD_LENGTH];
	WordNode* next;
	bool isEmpty;
	WordNode() :next(NULL), isEmpty(true) {};
	WordNode(char* myword):isEmpty(false),next(NULL) {
		strcpy(word, myword);
	}
	WordNode(char* myword,WordNode* mynext) :isEmpty(false),next(mynext) {
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
}

int explore(WordNode* List)
{
	for (WordNode* p = List; p->next != NULL; p = p->next)
	{
		cout << p->word << " ";
	}
	return OK;
}

void testmain()
{
	char filename[20];
	cin >> filename;

	WordNode* paper = new WordNode;
	getWordFromFile(filename, paper);
	explore(paper);
	system("pause");

}

void main()
{
	testmain();
}
