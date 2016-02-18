/*
 *                          18 MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#ifndef C5__CXX__ENV_H
#define C5__CXX__ENV_H

#include <vector>
#include <map>
#include <array>
#include <stack>
#include <memory>
#include <string>
#include <fstream>
#include "preprocessor.h"

namespace c5 {
namespace cxx {

enum options {
	help,
	debug,
	optimization,
	no_linking,
	no_assemble,
	only_preprocess,
	keep_comments,
	no_line,
	macro,
	undef,
	print_header,
	output,
	print_cmd,
	no_warning,
	all_warning,
	profiling,
	profiling_basic,
	print_functions,
	library,
	inc_dir,
	lib_dir,
	last
};

class Env {
public:

	Env();
	void set(options id, const std::string& a = "", 
		const std::string& b = "");
	std::string& get_output();
	std::map<std::string, std::unique_ptr<std::string>>& get_macros();
	bool is_undef(const std::string &name);
	bool is_set(options id);
	int get_optimization();
	std::vector<std::unique_ptr<std::string>>& get_lib_dir();
	std::vector<std::unique_ptr<std::string>>& get_inc_dir();
	std::vector<std::unique_ptr<std::string>>& get_lib();
	void dump();
	virtual void process_src(std::unique_ptr<std::string> src);
	virtual void process_inc(std::unique_ptr<std::string> include, bool is_local);
private:
	PreProcessor pre;
	std::array<int, options::last> values;
	std::vector<std::unique_ptr<std::string>> lib_dir;
	std::vector<std::unique_ptr<std::string>> inc_dir;
	std::vector<std::unique_ptr<std::string>> lib;
	std::map<std::string, 
		std::unique_ptr<std::string>> macros;
	std::map<std::string, 
		std::unique_ptr<std::string>> undef;
	std::string output;

	std::vector<std::unique_ptr<std::string>> files;	

	std::stack<size_t> files_stack;

	bool process_file_success(std::string &name);
};

} // cxx
} // c5

#endif // C5__CXX__ENV_H

