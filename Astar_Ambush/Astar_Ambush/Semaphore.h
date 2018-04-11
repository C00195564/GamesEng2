#pragma once
#include <condition_variable>

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

	void VAll()
	{
		std::unique_lock<decltype(m_mtx)> lock(m_mtx);
		++m_count;
		m_cv.notify_all();
	}
};