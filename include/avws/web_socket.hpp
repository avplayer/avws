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
public:
	/// Constructor.
	AVWS_DECL explicit web_socket(boost::asio::io_service &io)
		: m_ioservice(io)
	{
	}

	/// Destructor.
	AVWS_DECL virtual ~web_socket()
	{
	}

protected:

	boost::asio::io_service& m_ioservice;
};

} // namespace avws

#endif // AVWS_WEB_SOCKET_HPP
