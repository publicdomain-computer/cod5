/*
 *                          21 November  MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#ifndef C5__CXX__PREPROCESSOR_H
#define C5__CXX__PREPROCESSOR_H

#include <iostream>
#include "pretokens.h"

namespace c5 {
namespace cxx {

class Env;

class PreProcessor {
public:

	PreProcessor(Env &en);
	void process(std::istream &stream, size_t file);
	void set_is_directive(bool enable) {is_directive = enable;}
private:
	void translation3(char c);
	void check_pragma();
	void directive();
	Env &environ;
	size_t file;
	size_t line;
	size_t char_pos;

	std::string current;
	size_t cline;
	size_t cchar_pos;

	PreTokens tokens;

	bool skip;
	bool is_directive;;
};

} // cxx
} // c5

#endif // C5__CXX__PREPROCESSOR_H

