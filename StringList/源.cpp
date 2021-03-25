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

int append(WordNode*& list,char* myword)//�ڴʱ��׷��һ������
{
	WordNode* newnode = new WordNode(myword);//�ȴ���һ������ڵ�

	WordNode* p = list;
	if (p->isEmpty == true)//��������ǿյ�
	{
		list = newnode;//��ͷ�ڵ�����Ϊ�´����������ݵĽڵ�
		return OK;
	}

	for (p = list; p->next != NULL; p = p->next)//��ָ���ƶ����б�ĩβ
	{

	}
	p->next = newnode;//���½ڵ�׷����ĩβ
	return OK;
}

int getWordFromFile(char* filename,WordNode*& list)//���ļ���ȡ����
{
	FILE* fp = fopen(filename, "r");//���ļ�

	if (fp == NULL)//�ж��ļ��Ƿ�򿪳ɹ�
	{
		return ERROR;
	}

	char newword[MAX_WORD_LENGTH];
	while (fscanf(fp, "%s", &newword) != EOF)//��ͷ��ȡ�ļ�ֱ���ļ�β
	{
		append(list, newword);//����ȡ���ĵ���׷��������ĩβ
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
