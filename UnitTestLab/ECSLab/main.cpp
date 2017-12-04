#include "Entity.h"
#include "RenderSystem.h"
#include "AISystem.h"
#include "ControlSystem.h"

int main()
{
	Entity player;
	Entity cat;
	Entity dog;
	Entity alien;

	HealthComponent hc;
	PositionComponent pc;
	ControlComponent cc;

	player.addComponent(hc);
	player.addComponent(pc);
	player.addComponent(cc);

	alien.addComponent(hc);
	alien.addComponent(pc);

	cat.addComponent(hc);
	cat.addComponent(pc);

	dog.addComponent(hc);
	dog.addComponent(pc);

	AISystem as;
	RenderSystem rs;
	ControlSystem cs;

	as.addEntity(player);
	rs.addEntity(player);
	cs.addEntity(player);

	as.addEntity(alien);
	rs.addEntity(alien);

	as.addEntity(cat);
	rs.addEntity(cat);

	as.addEntity(dog);
	rs.addEntity(dog);

	bool running = true;

	while(running) 
	{
		as.update();
		rs.update();
		cs.update();
	}
	return 0;
}