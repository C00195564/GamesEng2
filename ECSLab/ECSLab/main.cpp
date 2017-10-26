#include "Entity.h"
#include "HealthSystem.h"
#include "Positionsystem.h"
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

	

	Healthsystem hs;
	PositionSystem ps;
	ControlSystem cs;

	hs.addEntity(player);
	ps.addEntity(player);
	cs.addEntity(player);

	bool running = true;
	while(running) 
	{
		hs.update();
		ps.update();
		cs.update();
	}
	return 0;
}