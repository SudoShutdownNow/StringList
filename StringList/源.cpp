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
	return OK;
}

int getWordFromInput(WordNode*& list)//�Ӽ��̶�ȡ����
{
	char newword[MAX_WORD_LENGTH];
	while (cin>>newword)//��ͷ��ȡ�ļ�ֱ���ļ�β
	{
		if (strcmp(newword, "`") == 0)
		{
			return OK;
		}
		append(list, newword);//����ȡ���ĵ���׷��������ĩβ
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//�ѿ���̨���óɺ�ɫ
			//cout << "***";
			cout << p->word <<" ";

		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
				FOREGROUND_GREEN | FOREGROUND_BLUE);//����̨����Ϊ��ɫ
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
	for (piter = paper; piter->next != NULL; piter = piter->next)//piter�ӵ�һ�����ʿ�ʼ����Paper
	{
		if (strcmp(titer->word, piter->word) == 0)//�ݴ���ͬ���ֿ�ʼ��λ��
		{
			label = piter;
		}
		while (strcmp(titer->word, piter->word) == 0)
		{
			if (titer->next == NULL)//һֱƥ�䵽Ŀ�괮��ĩβ�ˣ�˵��ƥ������
			{
				WordNode* oper = label;
				for (oper = label; oper != piter; oper = oper->next)//oper��paper�ϴ�labelλ�ÿ�ʼ��ֱ����ǰλ�ý���
				{
					cout << oper->word << endl;
					oper->labeled = true;//����Ǹ�Ϊ����
				}
				oper->labeled = true;//ͬ������һ�������

				titer = target;//��titer��λ
				//return OK;
			}

			if (piter->next != NULL)
			{
				//���Ŀ�괮û�е�ͷ��Ŀ�괮���ı���ָ��ͬʱ��ǰ�ƶ�
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
	cout << "�������ı���ַ��";
	cin >> filename;
	cout << "������Ҫ���ҵĴ���";
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
