//
// error_codec.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack.wgm at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_ERROR_CODEC_HPP
#define AVWS_ERROR_CODEC_HPP

#include <string>
#include <boost/system/system_error.hpp>
#include <boost/system/error_code.hpp>

#ifndef BOOST_SYSTEM_NOEXCEPT
#define BOOST_SYSTEM_NOEXCEPT BOOST_NOEXCEPT
#endif

namespace avws {

namespace detail {
	class error_category_impl;
}

template<class error_category>
const boost::system::error_category& error_category_single()
{
	static error_category error_category_instance;
	return reinterpret_cast<const boost::system::error_category&>(error_category_instance);
}

inline const boost::system::error_category& error_category()
{
	return error_category_single<detail::error_category_impl>();
}

namespace errc {

/// WEBSOCKET error codes.
/**
 * The enumerators of type @c errc_t are implicitly convertible to objects of
 * type @c boost::system::error_code.
 *
 * @par Requirements
 * @e Header: @c <error_codec.hpp> @n
 * @e Namespace: @c avws::errc
 */
enum errc_t
{
	// Client-generated errors.

	/// The response's status line was malformed.
	malformed_status_line = 1,

	/// The response's headers were malformed.
	malformed_response_headers = 2,

	/// The server-generated status code "401 Unauthorized".
	unauthorized = 401,

	/// The server-generated status code "402 Payment Required".
	payment_required = 402,

	/// The server-generated status code "403 Forbidden".
	forbidden = 403,

	/// The server-generated status code "404 Not Found".
	not_found = 404,

	/// The server-generated status code "405 Method Not Allowed".
	method_not_allowed = 405,
};

/// Converts a value of type @c errc_t to a corresponding object of type
/// @c boost::system::error_code.
/**
 * @par Requirements
 * @e Header: @c <error_codec.hpp> @n
 * @e Namespace: @c avws::errc
 */
inline boost::system::error_code make_error_code(errc_t e)
{
	return boost::system::error_code(static_cast<int>(e), avws::error_category());
}

} // namespace errc
} // namespace avws

namespace boost {
namespace system {

template <>
struct is_error_code_enum<avws::errc::errc_t>
{
  static const bool value = true;
};

} // namespace system
} // namespace boost

namespace avws {
namespace detail {

class error_category_impl
  : public boost::system::error_category
{
	virtual const char* name() const BOOST_SYSTEM_NOEXCEPT
	{
		return "HTTP";
	}

	virtual std::string message(int e) const
	{
		switch (e)
		{
		case errc::malformed_status_line:
			return "Malformed status line";
		case errc::malformed_response_headers:
			return "Malformed response headers";
		case errc::unauthorized:
			return "Unauthorized";
		case errc::payment_required:
			return "Payment required";
		case errc::forbidden:
			return "Forbidden";
		case errc::not_found:
			return "Not found";
		case errc::method_not_allowed:
			return "Method not allowed";
		default:
			return "Unknown WEBSOCKET error";
		}
	}

	virtual boost::system::error_condition default_error_condition(int e) const BOOST_SYSTEM_NOEXCEPT
	{
		switch (e)
		{
		case errc::unauthorized:
		case errc::forbidden:
			return boost::system::errc::permission_denied;
		case errc::not_found:
			return boost::system::errc::no_such_file_or_directory;
		default:
			return boost::system::error_condition(e, *this);
		}
	}
};

} // namespace detail

} // namespace avws

#endif // AVWS_ERROR_CODEC_HPP
