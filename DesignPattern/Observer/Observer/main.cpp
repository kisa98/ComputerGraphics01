#include <iostream>
#include <vector>

enum class UnitType {
	Marine,
	Medic,
	Firebat
};

//지휘관(ICommander)의 명령을 받는 유닛(옵저버)들
class IUnit {
protected:
	float m_posX = 0;
	float m_posY = 0;

public:
	size_t m_unitId = -1;
	std::string m_name = "NULL";
	virtual void move(float x, float y) = 0;
};

//유닛(옵저버)들의 구현(=구체화) 클래스
class BionicUnit : public IUnit {

public:
	BionicUnit() = delete; //유닛의 고유 번호와 타입은 반드시 설정해야함. 따라서 기본 생성자는 허용하지 않음.

	//다음처럼 구현을 강제하고 싶지만, 생성자는 가상화할 수 없음. 따라서 다른 방법을 찾아야함.
	//생성자를 가상화할 수 없는 것은 가상 함수 테이블 때문.
	BionicUnit(size_t unitId, UnitType type) {
		m_unitId = unitId;
		switch (type)
		{
		case UnitType::Marine:
			m_name = "Marine";
			break;
		case UnitType::Medic:
			m_name = "Medic";
			break;
		case UnitType::Firebat:
			m_name = "Firebat";
			break;
		default:
			break;
		}
		std::cout << "\t[" << m_name << "(" << unitId << ")] Reporting, Commander!" << std::endl;
	}

	void move(float x, float y) override {
		m_posX = x;
		m_posY = y;
		std::cout << "\t[" << m_name << "(" << m_unitId << ")] Roger. Move toward (" << x << ", " << y << ")!" << std::endl;
	}

};

//명령의 주체로 보통 Subject라고 표현함. 여기서는 유닛을 지휘하는 주체이므로 Commander로 명명
class ICommander {
public:
	virtual void selectUnit(IUnit* unit) = 0;
	virtual void deSelectUnit(IUnit* unit) = 0;
	virtual void move(float x, float y) = 0;
};

//지휘관 중 대장이라는 컨셉.
class Captain : public ICommander {
	
private:
	//싱글톤 기법으로 사용할 것이므로 정적 멤버로 객체 선언.
	static Captain* m_captain;

	//벡터에 유닛 포인터 저장. 포인터로 저장하면 객체를 복사하여 저장할 필요가 없음
	static std::vector<IUnit*> m_units;
	Captain() {
		std::cout << "[ Captain has been Operated. ]" << std::endl;
	}

	~Captain() {
		std::cout << "[ Captain has been Unoperated. ]" << std::endl;
	}
public:
	//정적 실체화 객체를 받는 함수.
	static Captain* getInstance() {
		if (m_captain == nullptr) {
			m_captain = new Captain();
		}
		return m_captain;
	}

	//실체화된 객체를 해제하는 함수. 안전 삭제가 적용되어 있음.
	static void Release() {
		if (m_captain != nullptr) {
			delete m_captain;
			m_captain = nullptr;
		}
	}

	//순수 가상(추상) 함수와 그 구현 함수가 static일 수 없는 이유?
	//static 함수는 특정 객체 인스턴스에 속하지 않고, 클래스 이름으로 호출됨
	//따라서 static 함수는 클래스 단계에서 동작하여, 특정 객체의 상태와 무관함.
	//덤으로 추상 함수는 추상 함수 테이블에서 관리되나, static 함수는 객체 인스턴스와 무관함.	
	void selectUnit(IUnit* unit) override {
		std::cout << "= Unit " << unit->m_name << "(" << unit->m_unitId << ") is Selected. =" << std::endl;
		m_units.push_back(unit);
	}

	void deSelectUnit(IUnit* unit) override {
		for (auto it = m_units.begin(); it != m_units.end(); ++it) {
			if (*it == unit) {

				std::cout << "= Unit " << (*it)->m_name << "(" << (*it)->m_unitId << ") is Selected. =" << std::endl;
				m_units.erase(it);
				return;
			}
		}
	}

	void move(float x, float y) override {
		std::cout << "[*Commander] Move Toward!" << "(" << x << ", " << y << ")" << std::endl;
		for (IUnit* unit : m_units) {
			unit->move(x, y);
		}
	}
};



Captain* Captain::m_captain = nullptr;
std::vector<IUnit*> Captain::m_units;

int main() {
	std::cout << "Hello World Base" << std::endl;
	Captain* me = Captain::getInstance();

	BionicUnit* unit0 = new BionicUnit(0, UnitType::Marine);
	BionicUnit* unit1 = new BionicUnit(1, UnitType::Medic);
	BionicUnit* unit2 = new BionicUnit(2, UnitType::Firebat);

	me->selectUnit(unit0);
	me->selectUnit(unit1);
	me->selectUnit(unit2);

	me->move(100, 100);

//	me->deSelectUnit(unit1);
	Captain::getInstance()->deSelectUnit(unit1);

	me->move(25, 25);

	Captain::Release();
}