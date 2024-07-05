#pragma once

//������ ����� ���Ǹ� �и��Ͽ� ���� ���ϴ�
//cpp�� ������ ���̺귯���� �����Ͽ� �����ϰ�,
//���� ������ cpp������ ������� �ʾ� �ڵ� ������ ����.

class State;

class Context {
public:
	State* m_pState;
	//���� ����
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


