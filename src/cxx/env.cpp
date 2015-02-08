/*
 *                          18 November MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#include <c5/cxx/env.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace c5::cxx;
using namespace std;

Env::Env() 
	: pre(*this)
{
	values.fill(0);
}

void Env::set(options id, const string &a, const string &b)
{
	switch (id) {
        case debug:
        case no_linking:
        case no_assemble:
        case only_preprocess:
        case keep_comments:
        case no_line:
        case print_header:
        case print_cmd:
        case no_warning:
        case all_warning:
        case profiling:
        case profiling_basic:
        case print_functions:
		values[id] = 1;
		break;
        case macro:
		macros[a] = unique_ptr<string>{new string{b}};
		break;
        case options::undef:
		undef[a] = unique_ptr<string>{new string{""}};
		break;
        case optimization:
		values[id] = stoi(a);
		break;
        case library:
		lib.push_back(unique_ptr<string>{new string{a}});
		break;
        case options::inc_dir:
		inc_dir.push_back(unique_ptr<string>{new string{a}});
		break;
        case options::lib_dir:
		lib_dir.push_back(unique_ptr<string>{new string{a}});
		break;
        case options::output:
		output = a;
		break;
	case help:
	case last:
	default:
		break;
	}
}

map<string, unique_ptr<string>>& Env::get_macros()
{
	return macros;
}

string& Env::get_output()
{
	return output;
}

bool Env::is_undef(const string &name)
{
	if (undef[name] != nullptr) return true;
	return false;	
}

bool Env::is_set(options id)
{
	if (values[id] != 0) return true;
	return false;
}

int Env::get_optimization()
{
	return 0;
}

vector<unique_ptr<string>>& Env::get_lib_dir()
{
	return lib_dir;
}

vector<unique_ptr<string>>& Env::get_inc_dir()
{
	return inc_dir;
}

vector<unique_ptr<string>>& Env::get_lib()
{
	return lib;
}

void Env::dump()
{
	cout << "* macros\n";
	for (auto it = macros.begin(); it != macros.end(); it++) {
		cout << it->first << " = " << *it->second.get() << "\n";
	}

	cout << "* include directories\n";
	for (auto it = inc_dir.begin(); it != inc_dir.end(); it++) {
		cout << *it->get() << "\n";
	}
		
}

void Env::process_src(string &src) 
{
        if (is_set(options::print_cmd)) {
                cout << "Compiling \"" <<  src << "\"...\n";
        }
	char p[PATH_MAX];
	if (!getcwd(p, PATH_MAX)) {
		throw std::runtime_error("too bad");
	}
	string s = p;
	s += "/";
	s += src;
	files.push_back(unique_ptr<string>{new string{s}});
	files_stack.push(files.size() - 1);
	
	ifstream is;
	is.open(s, ifstream::in);
	pre.process(is, files.size() - 1);
	files_stack.pop();
}

void Env::process_inc(string &include, bool is_local)
{
	if (is_local) {
		string s = *files[files_stack.top()].get();
		s.resize(s.rfind('/'));	
		s += "/";
		s += include;	
		if (process_file_success(s)) return;
	}

	for (auto it = inc_dir.begin(); it != inc_dir.end(); it++) {
		string s = *it->get();
		s += "/";
		s += include;
		if (process_file_success(s)) return;

	}
	if (is_local) {
		throw std::runtime_error("cannot open include \"" + 
			include + "\"");
	} else {
		throw std::runtime_error("cannot open include <" + 
			include + ">");
	}
}

bool Env::process_file_success(string &name)
{
  	struct stat buffer;   
  	if (stat(name.c_str(), &buffer) != 0) return false;

	files.push_back(unique_ptr<string>{new string{name}});
	files_stack.push(files.size() - 1);
        
	if (is_set(options::print_header)) {
                cout << "Processing \"" <<  name << "\"...\n";
        }

		
	ifstream is;
	is.open(name, ifstream::in);
	pre.process(is, files.size() - 1);
	files_stack.pop();
	return true;
}


