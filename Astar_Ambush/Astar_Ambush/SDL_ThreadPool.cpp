#include "SDL_ThreadPool.h"


SDL_mutex * SDL_ThreadPool::m_eventMutex;
bool SDL_ThreadPool::m_stopping;
std::queue<std::function<void()>> SDL_ThreadPool::m_tasks;

SDL_ThreadPool::SDL_ThreadPool(int num_threads)
{
	m_eventMutex = SDL_CreateMutex();
	m_stopping = false;
	start(num_threads);
}


SDL_ThreadPool::~SDL_ThreadPool()
{
	stop();
}

int threadfunc(void* data)
{
	
	SDL_ThreadPool::tFunc();

	return 0;
}


void SDL_ThreadPool::start(int num_threads)
{
	
	for (int i = 0; i < num_threads; i++)
	{
		m_threads.emplace_back(SDL_CreateThread(threadfunc, "worker " + i, (void*)i));
	}
}

void SDL_ThreadPool::stop()
{
	std::cout << "Joining threads" << std::endl;

	m_stopping = true;
	for (auto i : m_threads)
	{
		SDL_WaitThread(i, NULL);
	}
}

 /*
void SDL_ThreadPool::enqueue(std::function<void(void*)> func, void* args)
{
	SDL_LockMutex(m_eventMutex);
	m_tasks.emplace(std::bind(func, args));
	SDL_UnlockMutex(m_eventMutex);
}*/


//template<typename func>
void SDL_ThreadPool::enqueue(std::function<void()> func)
{
	SDL_LockMutex(m_eventMutex);
	m_tasks.emplace(func);
	SDL_UnlockMutex(m_eventMutex);
}

