/*
 *                          21 November MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 */

#include <c5/cxx/pretokens.h>
#include <c5/cxx/env.h>

using namespace c5::cxx;
using namespace std;

PreTokens::PreTokens(Env &en)
	: environ(en)
{
}

void PreTokens::push(string &str, size_t type, size_t file, size_t line,
	size_t char_pos)
{
	tokens.push_back(unique_ptr<PreToken>{
		new PreToken{unique_ptr<string>{new string{str}},
			type, file, line, char_pos}});
	string &s = *tokens.back().get()->identifier.get();
	cout << s << " ";
}

bool PreTokens::last_is_raw_string()
{
	if (tokens.empty()) return false;

	string &s = *tokens.back().get()->identifier.get();

	if (s == "R") return true;
	if (s == "LR") return true;
	if (s == "u8R") return true;
	if (s == "uR") return true;
	if (s == "UR") return true;
	return false;
}

