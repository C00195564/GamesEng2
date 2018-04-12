#pragma once

#include "stdafx.h"
#include "Grid.h"
#include <SDL_thread.h>
#include <SDL_mutex.h>
#include <functional>
#include <queue>

//pass in pointer of vector<CD_vector> for the path then have thread update that.
//update npc path
//npc checks for a change in the path vector. when it does, start again.

/// <summary>
/// Class which creates and manages a number of threads
/// functions(and their parameters) are places onto a queue for the threads to execute
/// </summary>
class SDL_ThreadPool
{
public:
	SDL_ThreadPool(int num_threads);
	~SDL_ThreadPool();
	
	//template<typename func>
	void enqueue(std::function<void()> func);

	/*void enqueue(std::function<void(void)> func, void* args);*/

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
					if (task == NULL)
					{
						std::cout << "Task not initialised" << std::endl;
					}
					m_tasks.pop();
				}
				SDL_UnlockMutex(m_eventMutex);
			}
			
			task();
			
			SDL_Delay(200);
		}
	}

	

private:
	static SDL_mutex * m_eventMutex;
	static bool m_stopping;
	static std::queue<std::function<void(void)>> m_tasks;
	std::vector<SDL_Thread*> m_threads;

	void start(int threads);
	void stop();
	
};

