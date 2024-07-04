#include <iostream>

class Coffee {
public:
	std::string m_name;
	std::string m_description;
	//가격을 선언하지 않으면 무료가 됩니다.
	int m_cost = 0;
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class Espresso : public Coffee {
public:
	Espresso(int cost = 10) {	
		m_cost = cost;
		m_name = "에스프레소";
		m_description = "커피 원액";
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

	//순수 가상 함수를 재선언하는 것은 데코레이터 패턴을 명확하게 명시함을 의미한다.
	//순수 가상 함수를 구현하지 않으면 어차피 추상 클래스로 취급하여, 생략해도 된다.
	virtual std::string getName() const = 0;
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class CubicIced : public IceDecorater {
public:
	CubicIced(Coffee* coffee) : IceDecorater(coffee) {}

	std::string getName() const override {
		return "큐브 얼음 " + m_coffee->getName();
	}

	std::string getDescription() const override {
		return "큐브 아이스가 추가된 " + m_coffee->getDescription();
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

	std::cout << "< Is-A 상속을 이용한 데코레이터 패턴 (사실 둘 다 씀) >" << std::endl;
	CubicIced* iceAmericano = new CubicIced(normalEspresso);
	std::cout << iceAmericano->getDescription() << " : " << iceAmericano->cost() << "$" << std::endl;


	std::cout << "< Has-A 컴포지션을 이용한 데코레이터 패턴 >" << std::endl;
	Water* ionWateredEspresso = new Water(normalEspresso, "이온 무르 ", "이온 워터가 첨가된 ", 3);
	std::cout << ionWateredEspresso->getName() << " : " << ionWateredEspresso->getDescription() << " : " << ionWateredEspresso->cost() << "$" << std::endl;

	return 0;
}