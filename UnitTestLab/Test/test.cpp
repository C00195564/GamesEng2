#include "pch.h"
#include "AISystem.h"
#include "HealthComponent.h"




void test(int i, HealthComponent *hc)
{

	hc->setHealth(50);
	if (i == 0)
	{
		hc->setHealth(100);
	}
	else
	{
		hc->setHealth(hc->getHealth() - i);
	}

	hc->setHealth(hc->getHealth() - 10);

}


TEST(ECSTest, EntityTest)
{
	HealthComponent *hc = new HealthComponent;
	test(0, hc);
	EXPECT_EQ(hc->getHealth(), 90);
}

TEST(ECSTest, ComponentTest)
{
	HealthComponent *hc = new HealthComponent;
	test(50, hc);
	EXPECT_EQ(hc->getHealth(), -10);
}

TEST(ECSTest, systemTest)
{
	HealthComponent *hc = new HealthComponent;
	test(30, hc);
	EXPECT_EQ(hc->getHealth(), 10);
}
