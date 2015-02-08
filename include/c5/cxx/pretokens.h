/*
 *                          21 November  MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#ifndef C5__CXX__PRETOKENS_H
#define C5__CXX__PRETOKENS_H

#include <list>
#include <memory>
#include <string>

namespace c5 {
namespace cxx {

class Env;

struct PreToken {
	std::unique_ptr<std::string> identifier;
	size_t type;
	size_t file;
	size_t line;
	size_t char_pos;
	int replace_index;
};

class PreTokens {
public:

	PreTokens(Env &en);
	void push (std::string &str, size_t type, size_t file, size_t line,
		size_t char_pos);
	bool last_is_raw_string();
	
private:
	Env &environ;
	std::list<std::unique_ptr<PreToken>> tokens;
};

} // cxx
} // c5

#endif // C5__CXX__PRETOKENS_H

