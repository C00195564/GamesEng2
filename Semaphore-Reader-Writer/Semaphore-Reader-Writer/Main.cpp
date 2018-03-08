#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

struct Semaphore
{
private:
	std::mutex m_mtx;
	std::unique_lock<std::mutex> m_lock;
	std::condition_variable m_cv;
	int m_count;

public:
	Semaphore(int i = 0) :m_count(i)
	{
		m_lock = std::unique_lock<std::mutex>(m_mtx);
	}

	void P()
	{
		while (m_count <= 0)
		{
			m_cv.wait(m_lock);
		}
		m_count--;
	}

	void V()
	{
		m_count++;
		m_cv.notify_one();
	}

	void Lock()
	{
		m_lock.lock();
	}

	void unlock()
	{
		m_lock.unlock();
	}
};


struct Database
{
public:
	Database()
	{
		for (int i = 0; i < 10; i++)
		{
			buffer[i] = 0;
		}
	}

	int buffer[10];

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
		mutexR.P();
		nr++;
		if (nr == 1)
		{
			rw.P();
			std::cout << "Readers turn for database" << std::endl;
		}
		mutexR.V();

		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		//read database
		std::cout << "reading database" << std::endl;

		mutexR.P();
		nr--;
		if (nr == 0)
		{
			std::cout << "Releasing the database" << std::endl;
			rw.V();
			
		}

		mutexR.V;
	}
}

void Writer()
{

	int i = 0;
	bool running = true;
	while (running)
	{

		rw.P();
		std::cout << "Writer taking database" << std::endl;

		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		//write to database
		std::cout << "Writing to database" << std::endl;
		db.buffer[0] = 2611;


		std::cout << "Writer releasing database" << std::endl;
		rw.V();
	}
}

int main()
{
	std::thread Reader1(Reader);
	std::thread Reader2(Reader);
	std::thread Reader3(Reader);

	std::thread Writer1(Writer);
	std::thread Writer2(Writer);

	Reader1.join();
	Reader2.join();
	Reader3.join();

	Writer1.join();
	Writer2.join();

	system("PAUSE");
	return 0;
}