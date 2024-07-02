/*##################################
�����带 �̿��� WinAPI����(������)
���ϸ�: WinAppDemo_Queueing.cpp
�ۼ���: ��ȫ�� (downkhg@gmail.com)
������������¥: 2020.12.15
����: 1.0 (���������)
###################################*/

#include <iostream>
#include <Windows.h>
#include <process.h>
#include <string>
#include <queue>

using namespace std;

enum WM_MSG { CREATE, COMMOND, PAINT, DESTROY, MAX };
string strMSG[MAX] = { "CREATE","COMMOND","PAINT","DESTROY" };

bool g_bLoop = true;

//arg�� ���� �ܺ��� �����Ͱ��� �������ִ�.
unsigned int WINAPI WndProc(void* arg)
{
	cout << "WndProc Start - arg:" << arg << endl;

	queue<int>* queData = (queue<int>*)arg;
	int nCount = 0;
	while (g_bLoop)
	{
		if (!queData->empty()) {
			int msg = queData->front();
			cout << "����� �۾��� �����մϴ�. �۾�: " << msg << endl;
			switch (msg)
			{
			case CREATE:
				cout << "�ʱ�ȭ" << endl;
				break;
			case COMMOND:
				cout << "����� �Է��ϼ���." << endl;
				for (int i = 0; i < MAX; i++)
					cout << i << ":" << strMSG[i];
				cout << endl;
				break;
			case PAINT:
				cout << "ȭ�鿡 �׸��ϴ�." << endl;
				break;
			case DESTROY:
				cout << "���α׷��� �����մϴ�." << endl;
				g_bLoop = false;
				break;
			default:
				break;
			}
			queData->pop();
			nCount++;
		}
		Sleep(2000);
	}
	cout << "WndProc End - arg:" << arg << endl;
	return 0;
}

//�Է��� �����鼭 ȭ�鿡 �޼����� �ʿ��� ����� ó���ϴ� ���α׷�.
//ť�� Ȱ���Ͽ� �޼����� ť�� �װ�, �����忡�� ť���� �����͸� 1���������� ó���ϴ� ���α׷����� �����.
//1. ť�� ���������� ���� ó���ϱ�.
//2. ť�� main�� ���������� ���� ������ ������ �����ϵ��� ó���ϱ�.

int main()
{
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;
	queue<int> queMsg;

	int nMSG = CREATE;
	cout << "Msg:" << &nMSG << endl;
	//���μ���: ���α׷��� ���� �⺻���� ó���� ����ϴ� �帧����(���η���), ū�帧����.
	//������: ���μ��� ���ο� ó���� �ϴ� �帧����(�ݺ����� ���ÿ� ó������), ū�帧 ������ ���� �帧.
	//������� ���α׷� ���ο��� ó���ϴ� ������ �����Ҽ� �־���ϹǷ�, 
	//�� ���α׷� ���� �Լ��� ȣ���Ͽ� ����Ѵ�.
	//�ݹ��Լ�: ���μ��������� ȣ�������ʰ�, �ܺο��� ȣ���ϵ��� �ϴ� �Լ�.
	hThread = (HANDLE)_beginthreadex(NULL, 0,
		WndProc,
		//(void*)&nMSG, 0,
		(void*)&queMsg, 0,
		(unsigned int*)dwThreadID);

	while (g_bLoop)
	{
		scanf_s("%d", &nMSG);
		queMsg.push(nMSG);
		cout << "ť�� �۾��� �����մϴ�. ���� �۾�: " << nMSG << endl;
	}

	return 0;
}