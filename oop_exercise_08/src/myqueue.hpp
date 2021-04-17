#pragma once 

#include <mutex>
#include <queue>

template<class T>
class MyQueue {
private:
	std::queue<T> q;
	std::mutex mute;
public:
	explicit MyQueue() noexcept : q(), mute() {}
	~MyQueue() {}

	bool Empty() {
		mute.lock();
		bool res = q.empty();
		mute.unlock();
		return res;
	}

	T Front() {
		mute.lock();
		T elem = q.front();
		mute.unlock();
		return elem;
	}

	void Pop() {
		mute.lock();
		q.pop();
		mute.unlock();
	}

	void Push(const T & elem) {
		mute.lock();
		q.push(elem);
		mute.unlock();
	}
};