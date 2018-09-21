/*
** EPITECH PROJECT, 2018
** babel
** File description:
** cpp epoll wrapper
*/

#include <sys/epoll.h>
#include <exception>
#include <functional>
#include <unordered_map>
#include <cinttypes>
#include <cstring>
#include <unistd.h>


namespace CC {

template<int T_nbr>
class EPollBase {
public:
	struct EPollHandler {
	public:
		using fctSignature = std::function<int (int)>; //ret -> error code -- arg -> fd

		EPollHandler(int fd, fctSignature const &);
		int		fd;
		fctSignature	hdl;
	};

	struct {
		using hookProto = std::function<void (EPollBase&)>;

		hookProto beforeWait;
		hookProto afterWait;
	}	hooks;

	explicit EPollBase();
	~EPollBase();

	inline EPollHandler*	add(int fd, typename EPollHandler::fctSignature const &hdl);
	inline void		wait(void);
private:
	inline void	_epollManagerExec(struct epoll_event *evt);

	int			_epollFd;
	struct epoll_event	_events[T_nbr];
	bool			_continue;
};

template<int T_nbr>
EPollBase<T_nbr>::EPollHandler::EPollHandler(int __fd, fctSignature const &__hdl) :
		fd(__fd),
		hdl(__hdl) {}

template<int T_nbr>
EPollBase<T_nbr>::EPollBase() :
			_epollFd(epoll_create1(0)),
			_continue(true)
	{
		if (_epollFd == -1) {
			throw std::runtime_error((std::string("Epoll Error: ") + std::strerror(errno)).c_str());  
		}
	}

template<int T_nbr>
EPollBase<T_nbr>::~EPollBase() {
	if (_epollFd != -1) {
		close(_epollFd);
	}
}

template<int T_nbr>
inline typename EPollBase<T_nbr>::EPollHandler*	EPollBase<T_nbr>::add(int fd, typename EPollHandler::fctSignature const &hdl) {
	struct epoll_event	evt;
	auto			*data = new EPollHandler(fd, hdl);

	if (data == nullptr) {
		throw std::runtime_error((std::string("Epoll Error: malloc: ") + std::strerror(errno)).c_str());
	}
	evt.data.ptr = data;
	evt.events = EPOLLIN;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, fd, &evt)) {
		throw std::runtime_error((std::string("Epoll Error: epoll_ctl: ") + std::strerror(errno)).c_str());
	}
	return (data);
}

template<int T_nbr>
inline void	EPollBase<T_nbr>::_epollManagerExec(struct epoll_event *evt)
{
	auto	*cur = static_cast<EPollHandler*>(evt->data.ptr);

	if ((evt->events & EPOLLERR) ||
	(evt->events & EPOLLHUP) ||
	(!(evt->events & EPOLLIN))) {
		if (cur->hdl(cur->fd) < 0)
			free(cur);
	} else if (cur) {
		if (cur->hdl(cur->fd) < 0)
			free(cur);
	}
}

template<int T_nbr>
inline void	EPollBase<T_nbr>::wait(void) {
	int	n = 0;

	while (this->_continue) {
		if (hooks.beforeWait != nullptr)
			hooks.beforeWait(*this);
		n = epoll_wait(this->_epollFd, this->_events, T_nbr, -1);
		if (hooks.afterWait != nullptr)
			hooks.afterWait(*this);
		for (int i = 0; i < n; i++)
			_epollManagerExec(this->_events + i);
	}
}

using EPoll = EPollBase<64>;

}