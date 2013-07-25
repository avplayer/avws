//
// settings.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack dot wgm at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// path LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AVWS_SETTINGS_HPP
#define AVWS_SETTINGS_HPP

#include <vector>
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>


namespace avws {

namespace avws_options {
	static const std::string status_code("_status_code");	// AVWS的状态码.
}

// 具体的websocket的option选项实现.

class option
{
public:
	// 定义option_item类型.
	typedef std::pair<std::string, std::string> option_item;
	// 定义option_item_list类型.
	typedef std::vector<option_item> option_item_list;
	// for boost::assign::insert
	typedef option_item value_type;
public:
	option() {}
	~option() {}

public:

	// 这样就允许这样的应用:
	// web_socket s;
	// s.request_options(request_opts()("opt", "XXXXXX"));
	option & operator()(const std::string &key, const std::string &val)
	{
		insert(key, val);
		return *this;
	}

	// 添加选项, 由key/value形式添加.
	void insert(const std::string &key, const std::string &val)
	{
		m_opts.push_back(option_item(key, val));
	}

	// 添加选项，由 std::part 形式.
	void insert(value_type & item)
	{
		m_opts.push_back(item);
	}

	// 删除选项.
	void remove(const std::string &key)
	{
		for (option_item_list::iterator i = m_opts.begin(); i != m_opts.end(); i++)
		{
			if (i->first == key)
			{
				m_opts.erase(i);
				return;
			}
		}
	}

	// 查找指定key的value.
	bool find(const std::string &key, std::string &val) const
	{
		std::string s = key;
		boost::to_lower(s);
		for (option_item_list::const_iterator f = m_opts.begin(); f != m_opts.end(); f++)
		{
			std::string temp = f->first;
			boost::to_lower(temp);
			if (temp == s)
			{
				val = f->second;
				return true;
			}
		}
		return false;
	}

	// 查找指定的 key 的 value. 没找到返回 ""，　这是个偷懒的帮助.
	std::string find(const std::string & key) const
	{
		std::string v;
		find(key,v);
		return v;
	}

	// 得到Header字符串.
	std::string header_string() const
	{
		std::string str;
		for (option_item_list::const_iterator f = m_opts.begin(); f != m_opts.end(); f++)
		{
			if (f->first != avws_options::status_code)
				str += (f->first + ": " + f->second + "\r\n");
		}
		return str;
	}

	// 清空.
	void clear()
	{
		m_opts.clear();
	}

	// 返回所有option.
	option_item_list& option_all()
	{
		return m_opts;
	}

	// 返回当前option个数.
	int size() const
	{
		return m_opts.size();
	}

protected:
	option_item_list m_opts;
};

typedef option request_opts;
typedef option response_opts;



// Http请求的代理设置.

struct proxy_settings
{
	proxy_settings()
		: type (none)
	{}

	std::string hostname;
	int port;

	std::string username;
	std::string password;

	enum proxy_type
	{
		// 没有设置代理.
		none,
		// socks4代理, 需要username.
		socks4,
		// 不需要用户密码的socks5代理.
		socks5,
		// 需要用户密码认证的socks5代理.
		socks5_pw,
		// http代理, 不需要认证.
		http,
		// http代理, 需要认证.
		http_pw,
	};

	proxy_type type;
};

} // namespace avhttp

#endif // AVWS_SETTINGS_HPP
