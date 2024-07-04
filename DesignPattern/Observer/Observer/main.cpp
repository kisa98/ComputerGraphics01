#include <iostream>
#include <vector>

enum class UnitType {
	Marine,
	Medic,
	Firebat
};

class IUnit {
protected:
	float m_posX = 0;
	float m_posY = 0;

public:
	size_t m_unitId = -1;
	std::string m_name = "NULL";
	virtual void move(float x, float y) = 0;
};

class BionicUnit : public IUnit {

public:
	BionicUnit() = delete;
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

class ICommander {
public:
	virtual void selectUnit(IUnit* unit) = 0;
	virtual void deSelectUnit(IUnit* unit) = 0;
	virtual void move(float x, float y) = 0;
};

class Captain : public ICommander {
	
private:
	static Captain* m_captain;
	static std::vector<IUnit*> m_units;
	Captain() {
		std::cout << "[ Captain has been Operated. ]" << std::endl;
	}

	~Captain() {
		std::cout << "[ Captain has been Unoperated. ]" << std::endl;
	}
public:
	static Captain* getInstance() {
		if (m_captain == nullptr) {
			m_captain = new Captain();
		}
		return m_captain;
	}

	static void Release() {
		if (m_captain != nullptr) {
			delete m_captain;
			m_captain = nullptr;
		}
	}

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

	me->deSelectUnit(unit1);

	me->move(25, 25);

	Captain::Release();
}