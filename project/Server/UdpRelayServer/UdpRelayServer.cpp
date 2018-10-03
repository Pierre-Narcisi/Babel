/*
** EPITECH PROJECT, 2018
** babel
** File description:
** UdpRelayServer.cpp
*/

#include <random>
#include <climits>
#include <iostream>
#include <boost/bind.hpp>
#include "UdpRelayServer.hpp"

namespace srv {

constexpr std::size_t const	bufferReceiveSize = sizeof(std::uint64_t); 
constexpr std::size_t const	bufferSendSize = sizeof(std::uint32_t) + sizeof(std::uint16_t); 

UdpRelayServer::UdpRelayServer(::boost::asio::io_context &ios):
	_ios(ios),
	_socket(ios),
	_bufferReceive(new char[bufferReceiveSize]), 
	_bufferSend(new char[bufferSendSize]) {}

void		UdpRelayServer::start(void) {
	_openSocketOnRandomPort();
}

void	UdpRelayServer::_openSocketOnRandomPort(void) {
	boost::system::error_code		error;
	std::random_device 			r;
	std::default_random_engine		generator(r());
	std::uniform_int_distribution<int>	distribution(1000, USHRT_MAX);
	
	while (1) {
		int randomPort = distribution(generator);
		_endpoint = boost::asio::ip::udp::endpoint(
			boost::asio::ip::udp::v4(),
			randomPort);
		
		_socket.open(_endpoint.protocol(), error);
		if (error) {
			_socket.close();
  			continue;
		}
		_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
		_socket.bind(_endpoint, error);
		if (error) {
			_socket.close();
  			continue;
		}
		std::cout << "UDP relay: Start listening on " << randomPort << std::endl;
		_listenerPort = randomPort;
		break;
	}
	_startReceive();
}

void	UdpRelayServer::_startReceive(void) {
	_socket.async_receive_from(
		boost::asio::buffer(_bufferReceive.get(), bufferReceiveSize), _endpoint,
		boost::bind(&UdpRelayServer::_handleReceive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void	UdpRelayServer::_handleReceive(const boost::system::error_code& error, std::size_t)
{
	std::cout << "Request ip of "
		<< *(reinterpret_cast<std::uint64_t*>(_bufferReceive.get()))
		<< std::endl;
	_startReceive();
}

}