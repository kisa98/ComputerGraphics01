#include <iostream>

class Coffee {
protected:
	//������ �������� ������ ���ᰡ �˴ϴ�.
	int m_cost = 0;

public:
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class Espresso : public Coffee {
public:
	Espresso(int cost = 10) {	
		m_cost = cost;
	}

	std::string getDescription() const override {
		return "����������";
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
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class CubicIced : public IceDecorater {
public:
	CubicIced(Coffee* coffee) : IceDecorater(coffee) {}

	std::string getDescription() const override {
		return "ť�� ���̽� " + m_coffee->getDescription();
	}

	int cost() const override {
		return 2 + m_coffee->cost();
	}
};


int main() {
	std::cout << "Cafe Hello World" << std::endl;
	std::cout << "===== MENU =====" << std::endl;
	Espresso* normalAmericano = new Espresso(10);
	std::cout << normalAmericano->getDescription() << " : " << normalAmericano->cost() << "$" << std::endl;

	CubicIced* iceAmericano = new CubicIced(normalAmericano);
	std::cout << iceAmericano->getDescription() << " : " << iceAmericano->cost() << "$" << std::endl;
	return 0;
}