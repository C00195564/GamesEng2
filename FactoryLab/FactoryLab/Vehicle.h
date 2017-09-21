#pragma once


class Vehicle {
public:
	Vehicle() {};
	virtual ~Vehicle() {};

	virtual void draw() = 0;

};