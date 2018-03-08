#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#define BUFF_LENGTH 10

int buf;
int p = 0;
int c = 0;


void Producer()
{
	int a[BUFF_LENGTH] = {10,20,30,40,50,60,70,80,90,100};

	bool run = true;
	while(run)
	{
		while (p < BUFF_LENGTH)
		{
			std::cout << "producer thread ID: " << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			while (p != c)
			{
				std::cout << "spinning" << std::endl;
			}
			buf = a[p];
			std::cout << a[p] << " deposited in buffer" << std::endl;
			p = p + 1;
		}
		std::cout << "Production finished" << std::endl;
		run = false;
	}
}

void Consumer()
{
	int b[BUFF_LENGTH];
	bool run = true;
	while (run)
	{
		while (c < BUFF_LENGTH)
		{
			std::cout << "Consumer thread ID: " << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			while (p <= c)
			{
				std::cout << "spinning" << std::endl;
			}
			//<await(p >c);>
			b[c] = buf;
			std::cout << buf << " deposited in b[]" << std::endl;
			c = c + 1;
		}
		std::cout << "consumer finished" << std::endl;
		run = false;
	}
}

int main()
{
	std::thread producer(Producer);
	std::thread consumer(Consumer);

	producer.join();
	consumer.join();


	system("PAUSE");
	return 0;
}