#include <iostream>

//싱글톤 
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
	static CSingleObject* m_pSingleObject;	//동적 할당 객체(인스턴스)를 연관 관계를 활용하여 관리한다. 참조 관계를 클래스 내부에 저장해서 쓰는게 연관 관계.

	CSingleObject() {
		//객체 생성전에 호출되는 정적 멤버 함수에서는 this를 호출 할 수 없다.
		//std::cout << "CSingleObject Constructed at [" << this << "]" << std::endl;
		std::cout << "CSingleObject GetInstance() " << std::endl;

	}

	~CSingleObject() {
		std::cout << "CSingleObject Destructed " << std::endl;
	}
public:
	/*
	//정적 지역 변수를 활용하여 싱글톤 할 수 있으나, 다른 객체 지향 언어에서 사용할 수 없음.
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
		return m_pSingleObject; //객체가 호출될 때마다 생성되어 싱글톤이 아니고, 각자 객체의 참조를 생성된 객체가 책임질 수 없음.
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

//정적 멤버 변수: 정적 멤버 변수는 객체가 생성전에 할당되야 하는데, C에서 함수 호출 전에 생성할 수 있는 변수는 전역변수 밖에 없어서, 이런식으로 문법을 작성해야한다.
CSingleObject* CSingleObject::m_pSingleObject = nullptr; 

void testMain() {
	//다음과 같이 객체가 생성가능하면, 이 객체를 싱글톤이라 할 수 없다.
	CNonSingleObject cNonSingleObject;
	CNonSingleObject arrNonSingleObject[2];

	//객체의 포인터만 선언했으므로, 객체는 생성되지 않음
	//CSingleObject* pSingleObject = NULL;
	//CSingleObject& refSingleObject = pSingleObject->GetInstance();
	//refSingleObject.display();	//객체 인스턴스가 아직 생성되지 않았으므로, 멤버에 접근하는 것이 불가(없으니까).

	//CSingleObject* pSingleObject = pSingleObject->GetInstance(); //이게 되는 이유는 멤버 변수에 접근한 적이 없어서. 그러나, NULL에 접근해서 쓰는 방식은 비상식적
	CSingleObject* pSingleObject = CSingleObject::GetInstance(); //static은 객체의 생성 여부와 상관없이 접근할 수 있음.
	CSingleObject::Release();
	pSingleObject = nullptr;
}


int main() {
	testMain();
}