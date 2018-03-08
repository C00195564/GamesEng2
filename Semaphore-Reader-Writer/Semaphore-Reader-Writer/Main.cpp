#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <time.h>

class Semaphore
{
private:
	std::mutex m_mtx;
	std::condition_variable m_cv;
	int m_count;

public:
	Semaphore(int i = 1) :m_count(i)
	{
	}

	void P()
	{
		std::unique_lock<decltype(m_mtx)> lock(m_mtx);
		while (m_count <= 0)
		{
			m_cv.wait(lock);
		}
		--m_count;
	}

	void V()
	{
		std::unique_lock<decltype(m_mtx)> lock(m_mtx);
		++m_count;
		m_cv.notify_one();
	}
};


class Database
{
public:
	Database()
	{
		for (int i = 0; i < 10; i++)
		{
			storage[i] = 0;
		}
		bufPos = 0;
	}

	void WriteTo(int num)
	{
		storage[bufPos] = num;
		bufPos = (bufPos + 1) % 10;
	}

	int ReadFrom(int position)
	{
		return storage[position];
	}

private:
	int storage[10];
	int bufPos;
};

Database db;
Semaphore rw;
unsigned int nr = 0;
Semaphore mutexR;

void Reader()
{
	bool running = true;
	while (running)
	{
		mutexR.P();//pmutexR
		nr++;//nr = nr+1
		if (nr == 1)//if nr == 1
		{
			rw.P();//p(rw)
			std::cout << "Readers turn for database" << std::endl;
			
		}
		mutexR.V();//P(mutexR)

		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		//read database
		for (int pos = 0; pos < 10; pos++)
		{
			std::cout << "reading: " << db.ReadFrom(pos) << " from the database" << std::endl;
		}


		mutexR.P();//P(mutexR)
		nr--;//nr = nr-1

		if (nr == 0)//if(nr == 0)
		{
			std::cout << "Releasing the database from readers" << std::endl;
			rw.V();//V(rw)
			
		}
		mutexR.V();//V(mutexR)

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Writer()
{
	bool running = true;
	while (running)
	{

		rw.P();
		std::cout << "Writer taking database" << std::endl;

		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		//write to database
		int num = rand() % 100 + 1;
		std::cout << "Writing: " << num << " to database" << std::endl;

		db.WriteTo(num);


		std::cout << "Writer releasing database" << std::endl;
		rw.V();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	srand(time(NULL));

	std::thread Reader1(Reader);
	std::thread Reader2(Reader);

	std::thread Writer1(Writer);
	std::thread Writer2(Writer);

	Reader1.join();
	Reader2.join();

	Writer1.join();
	Writer2.join();

	system("PAUSE");
	return 0;
}