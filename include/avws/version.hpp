//
// version.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2013 Jack (jack at gmail dot com)
//
// Distributed under the GNU Affero General Public License, Version 3.0. (See accompanying
// file LICENSE or copy at http://www.gnu.org/licenses/agpl-3.0.txt)
//

#ifndef AVWS_VERSION_HPP
#define AVWS_VERSION_HPP

#define AVWS_VERSION_MAJOR 0
#define AVWS_VERSION_MINOR 0
#define AVWS_VERSION_TINY 1

// the format of this version is: MMmmtt
// M = Major version, m = minor version, t = tiny version
#define AVWS_VERSION_NUM ((AVWS_VERSION_MAJOR * 10000) + (AVWS_VERSION_MINOR * 100) + AVWS_VERSION_TINY)
#define AVWS_VERSION "0.0.1"
#define AVWS_VERSION_MIME "avws/" AVWS_VERSION

#endif // AVWS_VERSION_HPP
