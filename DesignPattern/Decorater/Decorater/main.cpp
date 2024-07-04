#include <iostream>

class Coffee {
public:
	std::string m_name;
	std::string m_description;
	//������ �������� ������ ���ᰡ �˴ϴ�.
	int m_cost = 0;
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class Espresso : public Coffee {
public:
	Espresso(int cost = 10) {	
		m_cost = cost;
		m_name = "����������";
		m_description = "Ŀ�� ����";
	}
	
	std::string getName() const override {
		return m_name;
	}

	std::string getDescription() const override {
		return m_description;
	}

	int cost() const override {
		return m_cost;
	}
};

class IceDecorater : public Coffee {
protected:
	Coffee* m_coffee;

public:
	IceDecorater(Coffee* coffee) : m_coffee(coffee) {};

	//���� ���� �Լ��� �缱���ϴ� ���� ���ڷ����� ������ ��Ȯ�ϰ� ������� �ǹ��Ѵ�.
	//���� ���� �Լ��� �������� ������ ������ �߻� Ŭ������ ����Ͽ�, �����ص� �ȴ�.
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class CubicIced : public IceDecorater {
public:
	CubicIced(Coffee* coffee) : IceDecorater(coffee) {}

	std::string getName() const override {
		return "ť�� ���� " + m_coffee->getName();
	}

	std::string getDescription() const override {
		return "ť�� ���̽��� �߰��� " + m_coffee->getDescription();
	}

	int cost() const override {
		return 2 + m_coffee->cost();
	}
};

class Topping {
protected:
	Coffee* m_coffee;

public:
	std::string m_name;
	std::string m_description;
	int m_cost;
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0; 
	virtual int cost() const = 0;
};

class Water : public Topping {
public:
	Water() = delete;
	Water(Coffee* coffee, std::string name, std::string description, int cost) {
		m_name = name;
		m_description = description;
		m_cost = cost;
		m_coffee = coffee;
	}

	std::string getName() const override {
		return m_name + m_coffee->getName();
	}

	std::string getDescription() const override {
		return m_description + m_coffee->getDescription();
	}

	int cost() const override {
		return m_cost + m_coffee->cost();
	}
};

int main() {
	std::cout << "Cafe Hello World" << std::endl;
	std::cout << "===== MENU =====" << std::endl;
	Espresso* normalEspresso = new Espresso(10);
	std::cout << normalEspresso->m_name << " : " << normalEspresso->getDescription() << " : " << normalEspresso->cost() << "$" << std::endl;

	std::cout << "< Is-A ����� �̿��� ���ڷ����� ���� (��� �� �� ��) >" << std::endl;
	CubicIced* iceAmericano = new CubicIced(normalEspresso);
	std::cout << iceAmericano->getDescription() << " : " << iceAmericano->cost() << "$" << std::endl;


	std::cout << "< Has-A ���������� �̿��� ���ڷ����� ���� >" << std::endl;
	Water* ionWateredEspresso = new Water(normalEspresso, "�̿� ���� ", "�̿� ���Ͱ� ÷���� ", 3);
	std::cout << ionWateredEspresso->getName() << " : " << ionWateredEspresso->getDescription() << " : " << ionWateredEspresso->cost() << "$" << std::endl;

	return 0;
}