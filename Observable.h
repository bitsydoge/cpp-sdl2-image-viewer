#pragma once
#include "src/hdr/Observer.h"
#include <unordered_set>

template <class T, class ...Args>
class Observable
{
public:
	Observable() {
	}

	void addObserver(Observer<T, Args...>& obs) {
		m_head.emplace(&obs);
	}

	void removeObserver(Observer<T, Args...>& obs) {
		m_head.erase(&obs);
	}

	bool notifyObservers(T& t, Args... args) {
		auto hasBeenHandled = false;
		for (auto& obs : m_head) {
			hasBeenHandled |= obs->receive(t, std::forward<Args&>(args)...);
		}
		return hasBeenHandled;
	}


	virtual ~Observable() = default;

private:
	std::unordered_set<Observer<T, Args...>*> m_head;
};

template <class ...ET>
class EventDispatcher : public Observable<ET>... {
public:
	EventDispatcher() = default;
	EventDispatcher(const EventDispatcher<ET...>&) = delete;

	template <class ...ET2>
	void addMultipleObservers(Observer<ET2>&... obs) {
		int _[] = { 0, (Observable<ET2>::addObserver(obs), 0)... };
		(void)_;
	}

	template <class ...ET2>
	void removeMultipleObservers(Observer<ET2>&... obs) {
		int _[] = { 0, (Observable<ET2>::removeObserver(obs), 0)... };
		(void)_;
	}

	virtual ~EventDispatcher() = default;
};