#include "pch.h"
#include <iostream>
#include <map>
#include <string>
using namespace std; 

typedef enum {
	PIN_HIGH,
	PIN_LOW,
	PIN_TOGGLE
} pinState_t;

map<pinState_t, string> pinDict = {
	{PIN_HIGH, "PIN_HIGH"},
	{PIN_LOW, "PIN_LOW"},
	{PIN_TOGGLE, "PIN_TOGGLE"}
};

void bsp_pinWrite(pinState_t state, int pinNumber) {
	cout << "set pin number " << pinNumber << " to " << pinDict[state] << endl; 
}

void bsp_busWrite(pinState_t state, int busId) {
	cout << "wrote " << pinDict[state] << " to bus ID #" << busId << endl;
}

// Digital Output interface class
class DigitalOutputInterface {
public:
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void toggle() = 0;
};

class ControllerDigitalOutput : public DigitalOutputInterface {
private:
	int pinNumber;

public:
	ControllerDigitalOutput(int pinNumber) {
		this->pinNumber = pinNumber; 
	}

	void on(void) {
		bsp_pinWrite(PIN_HIGH, pinNumber);
	}

	void off(void) {
		bsp_pinWrite(PIN_LOW, pinNumber);
	}

	void toggle(void) {
		bsp_pinWrite(PIN_TOGGLE, pinNumber);
	}
};

class BusDigitalOutput : public DigitalOutputInterface {
private:
	int busId;

public:
	BusDigitalOutput(int busId) {
		this->busId = busId;
	}

	void on(void) {
		bsp_busWrite(PIN_HIGH, busId);
	}

	void off(void) {
		bsp_busWrite(PIN_LOW, busId);
	}

	void toggle(void) {
		bsp_busWrite(PIN_TOGGLE, busId);
	}
};


int main()
{
	ControllerDigitalOutput controllerPin(5);
	BusDigitalOutput busPin(0b1000);

	controllerPin.on();
	busPin.on(); 

	controllerPin.off();
	busPin.off(); 
}

