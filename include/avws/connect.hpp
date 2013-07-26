//
// connect.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_CONNECT_HPP
#define AVWS_CONNECT_HPP

namespace avws {

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

} // namespace avws

#endif // AVWS_CONNECT_HPP
