#include <iostream>

//�̱��� 
class CNonSingleObject {
public:
	int m_nData;

	CNonSingleObject() {
		m_nData = 0;
		std::cout << "CNonSingleObject Constructed at [" << this << "]" << std::endl;
	}

	~CNonSingleObject() {
		std::cout << "CNonSingleObject Destructed [" << this << "]" << std::endl;
	}
private:

};

class CSingleObject {
private:
	static CSingleObject* m_pSingleObject;	//���� �Ҵ� ��ü(�ν��Ͻ�)�� ���� ���踦 Ȱ���Ͽ� �����Ѵ�. ���� ���踦 Ŭ���� ���ο� �����ؼ� ���°� ���� ����.

	CSingleObject() {
		//��ü �������� ȣ��Ǵ� ���� ��� �Լ������� this�� ȣ�� �� �� ����.
		//std::cout << "CSingleObject Constructed at [" << this << "]" << std::endl;
		std::cout << "CSingleObject GetInstance() " << std::endl;

	}

	~CSingleObject() {
		std::cout << "CSingleObject Destructed " << std::endl;
	}
public:
	/*
	//���� ���� ������ Ȱ���Ͽ� �̱��� �� �� ������, �ٸ� ��ü ���� ���� ����� �� ����.
	CSingleObject& GetInstance() {
		static CSingleObject cSingleObject;
		return cSingleObject; 
	}
	*/
	static int m_nData;

	static CSingleObject* GetInstance() {
		if (m_pSingleObject == nullptr) {
			m_pSingleObject = new CSingleObject();
		}
		return m_pSingleObject; //��ü�� ȣ��� ������ �����Ǿ� �̱����� �ƴϰ�, ���� ��ü�� ������ ������ ��ü�� å���� �� ����.
	}

	static void Release() {
		if (m_pSingleObject != nullptr) {
			delete m_pSingleObject;
			m_pSingleObject = nullptr;
		}
	}

	void display() {
		std::cout << typeid(this).name() << ": Display(" << m_nData << ")" << std::endl;
	}
};

//���� ��� ����: ���� ��� ������ ��ü�� �������� �Ҵ�Ǿ� �ϴµ�, C���� �Լ� ȣ�� ���� ������ �� �ִ� ������ �������� �ۿ� ���, �̷������� ������ �ۼ��ؾ��Ѵ�.
CSingleObject* CSingleObject::m_pSingleObject = nullptr; 

void testMain() {
	//������ ���� ��ü�� ���������ϸ�, �� ��ü�� �̱����̶� �� �� ����.
	CNonSingleObject cNonSingleObject;
	CNonSingleObject arrNonSingleObject[2];

	//��ü�� �����͸� ���������Ƿ�, ��ü�� �������� ����
	//CSingleObject* pSingleObject = NULL;
	//CSingleObject& refSingleObject = pSingleObject->GetInstance();
	//refSingleObject.display();	//��ü �ν��Ͻ��� ���� �������� �ʾ����Ƿ�, ����� �����ϴ� ���� �Ұ�(�����ϱ�).

	//CSingleObject* pSingleObject = pSingleObject->GetInstance(); //�̰� �Ǵ� ������ ��� ������ ������ ���� ���. �׷���, NULL�� �����ؼ� ���� ����� ������
	CSingleObject* pSingleObject = CSingleObject::GetInstance(); //static�� ��ü�� ���� ���ο� ������� ������ �� ����.
	CSingleObject::Release();
	pSingleObject = nullptr;
}


int main() {
	testMain();
}