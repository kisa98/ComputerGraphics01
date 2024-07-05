#include <iostream>
#include "State.h"


void StateThree::goNext(Context* context) {
	std::cout << "three" << std::endl;
}

void StateTwo::goNext(Context* context) {
	std::cout << "two" << std::endl;
	context->setState(new StateThree);
}

void StateOne::goNext(Context* context) {
	std::cout << "one" << std::endl;
	context->setState(new StateTwo());
}

StateOne::StateOne() {
	std::cout << typeid(*this).name() << std::endl;
}

void Context::setState(State* state) {
	m_pState = state;
}

void Context::goNext() {
	m_pState->goNext(this);
}