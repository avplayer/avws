//
// web_socket.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_WEB_SOCKET_HPP
#define AVWS_WEB_SOCKET_HPP

#include "avws.hpp"
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/asio/detail/config.hpp>

namespace avws {

using boost::asio::ip::tcp;

class web_socket : public boost::noncopyable
{
	// 使用枚举类型而不是static const int, 是方便可能被用于在switch中.
	enum op_code
	{
		op_code_continuation = 0x0,
		op_code_text = 0x1,
		op_code_binary = 0x2,
		op_code_data_unused = 0x3,
		op_code_close = 0x8,
		op_code_ping = 0x9,
		op_code_pong = 0xA,
		op_code_control_unused = 0xB,
	};

public:
	// Constructor.
	AVWS_DECL explicit web_socket(boost::asio::io_service &io)
		: m_ioservice(io)
	{
	}

	// Destructor.
	AVWS_DECL virtual ~web_socket()
	{
	}


	// 设置请求选项信息, 必须在open或accept之前设置.
	AVWS_DECL void request_options(const request_opts &options);
	// 返回当前连接的请求选项.
	AVWS_DECL request_opts request_options(void) const;
	// 返回当前连接的回复选项信息.
	AVWS_DECL response_opts response_options(void) const;

	// 在open或accept的步骤里, 实行了websocket认证.

	// 打开url.
	AVWS_DECL void open(const url &u);
	AVWS_DECL void open(const url &u, boost::system::error_code &ec);

	// 异步打开url.
	template <typename Handler>
	void async_open(const url &u, BOOST_ASIO_MOVE_ARG(Handler) handler);

	// 关闭底层连接.
	AVWS_DECL void close();
	AVWS_DECL void close(boost::system::error_code &ec);

	// 在websocket中, 数据封装成frame由发送函数实现, 上层用户无需操心.
	// 至于是文本还是二进制, 由request_options确定.

	// 同步发送一些数据.
	template <typename ConstBufferSequence>
	std::size_t write_some(const ConstBufferSequence &buffers);
	// 同步发送一些数据.
	template <typename ConstBufferSequence>
	std::size_t write_some(const ConstBufferSequence &buffers,
		boost::system::error_code &ec);

	// 异步发送一些数据.
	template <typename ConstBufferSequence, typename Handler>
	void async_write_some(const ConstBufferSequence &buffers, BOOST_ASIO_MOVE_ARG(Handler) handler);

	// 同步发送ping消息.
	AVWS_DECL void ping();
	AVWS_DECL void ping(boost::system::error_code &ec);

// 	// 同步发送带payload的ping消息.
// 	template <typename ConstBufferSequence>
// 	void ping(const ConstBufferSequence &buffers);
// 	template <typename ConstBufferSequence>
// 	void ping(const ConstBufferSequence &buffers, boost::system::error_code &ec);

	// 异步发送ping消息.
	template <typename Handler>
	void async_ping(BOOST_ASIO_MOVE_ARG(Handler) handler);
// 	// 异步发送payload的ping消息.
// 	template <typename ConstBufferSequence, typename Handler>
// 	void async_ping(const ConstBufferSequence &buffers, BOOST_ASIO_MOVE_ARG(Handler) handler);

	// 同步发送pong消息.
	AVWS_DECL void pong();
	AVWS_DECL void pong(boost::system::error_code &ec);

// 	// 同步发送带payload的pong消息.
// 	template <typename ConstBufferSequence>
// 	void pong(const ConstBufferSequence &buffers);
// 	template <typename ConstBufferSequence>
// 	void pong(const ConstBufferSequence &buffers, boost::system::error_code &ec);

	// 异步发送pong消息.
	template <typename Handler>
	void async_pong(BOOST_ASIO_MOVE_ARG(Handler) handler);
// 	// 异步发送payload的ping消息.
// 	template <typename ConstBufferSequence, typename Handler>
// 	void async_pong(const ConstBufferSequence &buffers, BOOST_ASIO_MOVE_ARG(Handler) handler);

	// 欠缺的考虑, FIN消息控制.


protected:

	boost::asio::io_service& m_ioservice;
};

} // namespace avws

#endif // AVWS_WEB_SOCKET_HPP
