//
// resolve.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_RESOLVE_HPP
#define AVWS_RESOLVE_HPP

namespace avws {

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

} // namespace avws

#endif // AVWS_RESOLVE_HPP
