#include <iostream>

class Coffee {
protected:
	//가격을 선언하지 않으면 무료가 됩니다.
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
		return "에스프레소";
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
	virtual std::string getDescription() const = 0;
	virtual int cost() const = 0;
};

class CubicIced : public IceDecorater {
public:
	CubicIced(Coffee* coffee) : IceDecorater(coffee) {}

	std::string getDescription() const override {
		return "큐브 아이스 " + m_coffee->getDescription();
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