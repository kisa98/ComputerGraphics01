#pragma once

//복잡한 선언과 정의를 분리하여 보기 편하다
//cpp의 내용을 라이브러리로 빌드하여 배포하고,
//실제 구현한 cpp파일이 노출되지 않아 코드 보안이 좋다.

class State;

class Context {
public:
	State* m_pState;
	//연관 관계
	void setState(State* state);
	void goNext();
};

class State {
public:
	virtual void goNext(Context* context) = 0;
};

class StateThree : public State {
public:
	void goNext(Context* context);
};

class StateTwo : public State {
public:
	void goNext(Context* context);
};

class StateOne : public State {
public:
	StateOne();
	void goNext(Context* context);
};


