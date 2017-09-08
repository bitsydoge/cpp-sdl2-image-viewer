#pragma once
#include <stdexcept>
#include <functional>


template <typename T, typename ...Args>
class Observable;

namespace detail {
	template <class T, class ...Args>
	class ObserverImpl {
	public:
		template <typename T1, typename ...Args1>
		friend class Observable;

		explicit ObserverImpl(std::function<bool(T&, Args...)> const& handler) : m_handler(handler) {
			if (m_handler == nullptr) {
				throw std::runtime_error("Error : Function cannot be null");
			}
		}

		virtual ~ObserverImpl() = default;

	private:
		std::function<bool(T&, Args...)> m_handler;

		bool receive(T& evt, Args&... args) {
			return (m_handler)(evt, std::forward<Args&>(args)...);
		}

	};
}

template <class T, class ...Args>
class Observer :
	public detail::ObserverImpl<T, Args...> {
public:
	explicit Observer(std::function<bool(T&, Args...)> const& handler, Observable<T, Args...>& observable) :
		detail::ObserverImpl<T, Args...>(handler),
		m_observable(observable) {
		m_observable.addObserver(*this);
	}

	virtual ~Observer() {
		m_observable.Observable<T, Args...>::removeObserver(static_cast<Observer<T, Args...>&>(*this));
	}

private:
	Observable<T, Args...>& m_observable;

};