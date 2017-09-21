#include <iostream>

using namespace std;

class DrawAPI
{
	//abstract class
public:
	virtual void Draw() = 0;
};

class DrawImpl : public DrawAPI
{
	//implementation of the abstract class
public:
	void Draw() { cout << "Draw Impl" << endl; }
};

class Character {
public:
	virtual void Draw() = 0;

};

class player : public Character {
public:
	player(DrawAPI* api) { this->api = api; }
	void Draw() { api->Draw(); }
private:
	DrawAPI* api;
};

int main(void)
{
	DrawAPI* api = new DrawImpl();
	Character* character = new player(api);
	character->Draw();
	system("Pause");
}