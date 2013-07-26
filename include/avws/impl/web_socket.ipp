//
// web_socket.ipp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_WEB_SOCKET_IPP
#define AVWS_WEB_SOCKET_IPP

namespace avws {

web_socket::web_socket(boost::asio::io_service &io)
	: m_io_service(io)
	, m_resolver(io)
	, m_socket(io)
{
}

web_socket::~web_socket()
{
}

void web_socket::request_options(const request_opts &options)
{

}

request_opts web_socket::request_options(void) const
{
	request_opts opt;
	return opt;
}

response_opts web_socket::response_options(void) const
{
	response_opts opt;
	return opt;
}

// 同步查询url中host信息, 并返回相应的iterator.
tcp::resolver::iterator resolve_host(tcp::resolver &resolver,
	const url &u, boost::system::error_code &ec)
{
	std::ostringstream port_string;
	port_string.imbue(std::locale("C"));
	port_string << u.port();
	tcp::resolver::query query(u.host(), port_string.str());
	return resolver.resolve(query, ec);
}

// 同步连接到endpoint_iterator所指的host.
template <typename Socket>
void connect_host(Socket &s,
	tcp::resolver::iterator &endpoint_iterator, boost::system::error_code &ec)
{
	tcp::resolver::iterator end;
	// 尝试连接解析出来的代理服务器地址.
	ec = boost::asio::error::host_not_found;
	while (ec && endpoint_iterator != end)
	{
		s.close(ec);
		s.connect(*endpoint_iterator++, ec);
	}
}

void web_socket::open(const url &u)
{
	boost::system::error_code ec;
	open(u, ec);
	if (ec)
	{
		boost::throw_exception(boost::system::system_error(ec));
	}
}

void web_socket::open(const url &u, boost::system::error_code &ec)
{
	// 保存url相关的信息.
	m_protocol = u.protocol();
	m_url = u;

	// 输出打开的链接地址.
	LOG_DEBUG("Sync open url \'" << u.to_string() << "\'");

	// 判断不支持的协议, 并返回错误.
	if (m_protocol != "ws")
	{
		LOG_ERROR("Unsupported scheme \'" << m_protocol << "\'");
		ec = boost::asio::error::operation_not_supported;
		return;
	}

	// 解析url主机
	tcp::resolver::iterator endpoint_iterator = resolve_host(m_resolver, m_url, ec);
	if (ec)	// 解析域名出错, 直接返回相关错误描述.
	{
		LOG_ERROR("Resolve \'" << m_url.host() <<
			"\', error message \'" << ec.message() << "\'");
		return;
	}

	connect_host(m_socket, endpoint_iterator, ec);
	if (ec)
	{
		LOG_ERROR("Connect to server \'" << m_url.host() << ":" << m_url.port() <<
			"\', error message \'" << ec.message() << "\'");
		return;
	}
	else
	{
		LOG_DEBUG("Connect to server \'" << m_url.host() << ":" << m_url.port() << "\'.");
	}

	// 连接成功, 开始认证逻辑.

}

template <typename Handler>
void web_socket::async_open(const url &u, BOOST_ASIO_MOVE_ARG(Handler) handler)
{

}

void web_socket::close()
{

}

void web_socket::close(boost::system::error_code &ec)
{

}
template <typename ConstBufferSequence>
std::size_t web_socket::write_some(const ConstBufferSequence &buffers)
{
	return -1;
}

template <typename ConstBufferSequence>
std::size_t web_socket::write_some(const ConstBufferSequence &buffers,
	boost::system::error_code &ec)
{
	return -1;
}

template <typename ConstBufferSequence, typename Handler>
void web_socket::async_write_some(
	const ConstBufferSequence &buffers, BOOST_ASIO_MOVE_ARG(Handler) handler)
{

}

template <typename MutableBufferSequence>
std::size_t web_socket::read_some(const MutableBufferSequence &buffers)
{
	return -1;
}

// 同步接收消息.
template <typename MutableBufferSequence>
std::size_t web_socket::read_some(const MutableBufferSequence &buffers,
	boost::system::error_code &ec)
{
	return -1;
}

// 异步接收消息.
template <typename MutableBufferSequence, typename Handler>
void web_socket::async_read_some(
	const MutableBufferSequence &buffers, BOOST_ASIO_MOVE_ARG(Handler) handler)
{

}



} // namespace avws

#endif // AVWS_WEB_SOCKET_IPP
