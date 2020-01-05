#pragma once
#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>

class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool(int _numThreads) { Start(_numThreads); }

	~ThreadPool() { Stop(); }

	void Enqueue(Task _task);

private:
	void Start(int _numThreads);
	void Stop();

	std::vector<std::thread> m_threads;

	std::condition_variable m_cv;

	std::mutex m_mtx;

	bool m_stopping;

	std::queue<Task> m_tasks;
};