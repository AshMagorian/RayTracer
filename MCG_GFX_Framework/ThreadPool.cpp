#include "ThreadPool.h"


void ThreadPool::Start(int _numThreads)
{
	m_stopping = false;
	for (int i = 0; i < _numThreads; ++i)
	{
		m_threads.emplace_back([=]
		{
			//The infinite loop keeps all threads running until the tasks are completed
			while (true)
			{
				Task task;
				{
					//Protects the shared data, is also used for the condition variable
					std::unique_lock<std::mutex> lock{ m_mtx };

					//Waits until there is a new task available or the destructor is called
					m_cv.wait(lock, [=] {return m_stopping || !m_tasks.empty(); });

					// Breaks from the loop if the destructor is called AND there are no more tasks left
					if (m_stopping && m_tasks.empty()) { break; }

					//Task is taken off of the queue
					task = std::move(m_tasks.front());
					m_tasks.pop();
				}
				//Runs the Task
				task();
			}	
		});
	}
}

void ThreadPool::Stop()
{
	{
		std::unique_lock<std::mutex> lock{ m_mtx };
		m_stopping = true;
	}

	//After setting m_stopping to true, all threads will now try to break out of their infinite loop
	m_cv.notify_all();

	//iterates through all threads in the vector and waits for them to finish
	for (auto &thread : m_threads)
	{
		thread.join();
	}
}

void ThreadPool::Enqueue(Task _task)
{
	{
		std::unique_lock<std::mutex> lock{ m_mtx };
		m_tasks.emplace(std::move(_task));
	}
	//Notifies a waiting thread to run a task
	m_cv.notify_one();
}