#pragma once

class Cell;
class Link
{
public:
	Link(Cell* cell) { m_neighbour = cell; m_weight = 1; };
	~Link() {};

	void SetWeight(int weight) { m_weight = weight; };
	int getWeight() { return m_weight; };
	Cell* getCell() { return m_neighbour; };
private:
	Cell * m_neighbour;
	int m_weight;
};

