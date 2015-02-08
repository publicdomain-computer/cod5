/*
 *                          18 November MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#include <c5/cxx/compiler.h>
#include <iostream>
#include <cstdlib>

using namespace c5;
using namespace c5::cxx;
using namespace std;

Compiler::Compiler()
{
}

int Compiler::run(vector<unique_ptr<string>>& args)
{
	if (args.size() < 2) {
		usage();
		return -1;
	}
	
	set_directories();

	for (int i = 1;  i < args.size(); i++) {
		string &s = *args[i].get();
		string t;
		string u;
		if (s[0] == '-') {
			switch (s[1]) {
			case 'h':
				usage();
				return 0;
			case 'g':
				env.set(options::debug);
				break;
			case 'O':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::optimization,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::optimization, t);
				}
				break;
			case 'c':
				env.set(options::no_linking);
				break;
			case 'S':
				env.set(options::no_assemble);
				break;
			case 'E':
				env.set(options::only_preprocess);
				break;
			case 'C':
				env.set(options::keep_comments);
				break;
			case 'P':
				env.set(options::no_line);
				break;
			case 'D':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					t = *args[i].get();
				} else {
					t = s.substr(2, string::npos);
							
				}
				{
					size_t j;
					j = t.find_first_of('=');
					if (j == string::npos) {
						u = "";
					} else {
						u = t.substr(j + 1, t.npos);
						t = t.substr(0, j);
					}
					env.set(options::macro, t, u);
				}
				break;
			case 'U':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::undef,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::undef, t);
				}
				break;
			case 'H':
				env.set(options::print_header);
				break;
			case 'o':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::output,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::output, t);
				}
				break;
			case 'v':
				env.set(options::print_cmd);
				break;
			case 'w':
				env.set(options::no_warning);
				break;
			case 'W':
				env.set(options::all_warning);
				break;
			case 'p':
				env.set(options::profiling);
				break;
			case 'a':
				env.set(options::profiling_basic);
				break;
			case 'Q':
				env.set(options::print_functions);
				break;
			case 'l':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::library,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::library, t);
				}
				break;
			case 'I':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::inc_dir,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::inc_dir, t);
				}
				break;
			case 'L':
				if (s[2] == 0) {
					i++;
					if (i >= args.size()) {
						usage();
						return -1;
					}
					env.set(options::lib_dir,
						*args[i].get());
				} else {
					t = s.substr(2, string::npos);		
					env.set(options::lib_dir, t);
				}
				break;
			default:
				usage();
				return -1;
			}
			
		} else {
			add_source(s);
		}
	}

	env.dump();

	if (sources.begin() == sources.end()) {
		usage();
		return -1;
	}
        for (auto it = sources.begin(); it != sources.end(); it++) {
		compile(*it->get());
        }


	return 0;
}

void Compiler::add_source(string &src)
{
	sources.push_back(unique_ptr<string>{new string{src}});
}

void Compiler::usage()
{
	cout << "\n";
	cout << "Usage: cxx [-options] filename\n";
	cout << "\n";
	cout << "  -h <text> Shows information regarding <text>\n";
	cout << "  -g Full symbolic debug\n";
	cout << "  -O[0-4] Optimization level (Default:2)\n";
	cout << "  -c Disable linking\n";
	cout << "  -S Do not assemble\n";
	cout << "  -E Run only the preprocessor\n";
	cout << "  -C Preprocessor does not discard comments\n";
	cout << "  -P Preprocessor does not generate #line directives\n";
	cout << "  -Dmacro[=def] Define a macro\n";
	cout << "  -Umacro Undefine a macro\n";
	cout << "  -H Print the name of all header file used\n";
	cout << "  -o file Write output in file\n";
	cout << "  -v Print commands executed at every stage of compilation\n";
	cout << "  -w Inhibit all warning messages\n";
	cout << "  -Wall Enables all warning messages\n";
	cout << "  -p Generate profiling extra code\n";
	cout << "  -a Generate profiling extra code for basic block\n";
	cout << "  -Q Print out each function name\n";
	cout << "  -llibrary Link against the library name library\n";
	cout << "  -Idir Add dir to the head of the list of "
		"headers directories\n";
	cout << "  -Ldir Add dir to the list of library directories\n";

}


void Compiler::compile(string &src)
{
	env.process_src(src);
}

void Compiler::set_directories()
{
	env.set(options::inc_dir, "/usr/include");
	env.set(options::inc_dir, "/usr/local/include");
}

