#pragma once
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_mutex.h>
#include <functional>
#include <queue>
#include "stdafx.h"


//pass in pointer of vector<CD_vector> for the path then have thread update that.
//update npc path
//npc checks for a change in the path vector. when it does, start again.

class SDL_ThreadPool
{
public:
	SDL_ThreadPool(int num_threads);
	~SDL_ThreadPool();
	
	template<typename func, typename... Args>
	auto enqueue(func function, Args&&... Args);

	static void tFunc()
	{
		while (true)
		{
			std::function<void()> task = [=] {};
			
			{
				SDL_LockMutex(m_eventMutex);
				if (m_stopping)
				{
					break;
				}
				if (!m_tasks.empty())
				{
					task = std::move(m_tasks.front());
					m_tasks.pop();
				}
				SDL_UnlockMutex(m_eventMutex);
			}
			
			task();
		}
	}

	

private:
	static SDL_mutex * m_eventMutex;
	static bool m_stopping;
	static std::queue<std::function<void()>> m_tasks;
	std::vector<SDL_Thread*> m_threads;

	void start(int threads);
	void stop();
	
};

