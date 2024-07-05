#include <iostream>
#include "State.h"

int main() {
	Context context;
	StateOne* stateOne = new StateOne();
	StateTwo* stateTwo = new StateTwo();
	StateThree* stateThree = new StateThree();

	context.setState(stateOne);
	context.goNext();
	context.goNext();
	context.goNext();
}
