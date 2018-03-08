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


#define LENGTH 10
#define THREAD_NUM 2

std::mutex mtx;

//int buffer[LENGTH];
int buffer[10];
int p = 0;
int c = 0;
int empty = LENGTH;
std::condition_variable cv_Empty;

int full;
std::condition_variable cv_Full;

int back = 0;
int front = 0;
 

void V(int &s)
{
	s++;
}

void P(int &s)
{
	s--;
}

void Producer()
{
	int a[LENGTH] = { 10,20,30,40,50,60,70,80,90,100 };
	bool run = true;
	while (run)
	{
		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		P(empty);
		mtx.lock();


		buffer[back] = a[p];
		std::cout << "Inserted: " << buffer[back] << " Into the buffer" << std::endl;
		back = (back + 1) % LENGTH;
		p = (p + 1) % LENGTH;

		mtx.unlock();
		V(full);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Consumer()
{
	int b[LENGTH];
	bool run = true;

	while (run)
	{

		std::cout << "ID: " << std::this_thread::get_id() << std::endl;

		P(full);
		mtx.lock();

		b[c] = buffer[front];
		std::cout << "Extracted: " << buffer[front] << " From the buffer" << std::endl;
		front = (front + 1) % LENGTH;
		c++;
		mtx.unlock();
		V(empty);
		std::this_thread::sleep_for(std::chrono::seconds(1));

	}
}

int main()
{
	std::thread prod_Thread1(Producer);
	//std::thread prod_Thread2(Producer);
	std::thread cons_thread1(Consumer);
	//std::thread cons_thread2(Consumer);

	prod_Thread1.join();
	//prod_Thread2.join();
	cons_thread1.join();
	//cons_thread2.join();

	system("PAUSE");
	return 0;
}