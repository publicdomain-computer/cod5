/*
 *                          15 November MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

 
#include <c5/cxx/compiler.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	vector<unique_ptr<string>> args;
	
	for (int i = 0; i < argc; i++) {
		args.push_back(make_unique<string>(argv[i]));
//		cout << string(argv[i]);
	}
	
	c5::cxx::Compiler app;
	return app.run(args);
}

