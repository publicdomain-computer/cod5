/*
 *                          18 MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#ifndef C5__CXX__COMPILER_H
#define C5__CXX__COMPILER_H

#include <vector>
#include <memory>
#include <string>
#include "env.h"

namespace c5 {
namespace cxx {

class Compiler {
public:
	Compiler();
	int run(std::vector<std::unique_ptr<std::string>>& args);

private:
	void usage();
	void add_source(std::unique_ptr<std::string> src);
	void compile(std::unique_ptr<std::string> src);
	void set_directories();

	std::vector<std::unique_ptr<std::string>> sources;
	cxx::Env env;
};

} // cxx 
} // c5

#endif // C5__CXX__COMPILER_H

