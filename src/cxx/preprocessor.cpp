/*
 *                          21 November MMXIV PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 * http://en.cppreference.com/w/cpp
 */

#include <c5/cxx/preprocessor.h> 
#include <c5/cxx/env.h>
#include <c5/cxx/pretokens.h>
#include <sstream>

using namespace c5::cxx;
using namespace std;

PreProcessor::PreProcessor(Env &en)
	: environ(en),
	tokens(en)
{
	skip = false;
	is_directive = false;
}

void PreProcessor::process(istream &s, size_t file)
{
	char c[3];
	size_t line = this->line;
	size_t char_pos = this->char_pos;
	size_t file_ = this->file;

	this->file = file;
	this->line = 0;
	this->char_pos = 0;
	while (s.get(c[0])) {
		if (c[0] == '?') {
			// 5.1.1.2 Translation phases 1)
			// Trigraph
			if (s.get(c[1])) {
				if (c[1] == '?') {
					if (s.get(c[2])) {
						this->char_pos += 2;
						switch (c[2]) {
						case '(':
							c[0] = '[';
							break;
						case '/':
							c[0] = '\\';
							break;
						case ')':
							c[0] = ']';
							break;
						case '\'':
							c[0] = '^';
							break;
						case '<':
							c[0] = '{';
							break;
						case '!':
							c[0] = '|';
							break;
						case '>':
							c[0] = '}';
							break;
						case '-':
							c[0] = '~';
							break;
						case '=':
							c[0] = '#';
							break;
						default:
							this->char_pos -= 2;
							s.putback(c[1]);
							s.putback(c[2]);
							break;
						}
						
					}
				} else {
					s.putback(c[1]);
				}
			}
		}

		if (c[0] == '\\') {
			// 5.1.1.2 Translation phases 2)
                        // backslash is the last character
                        // before the newline then the newline and
                 	// \ are deleted
			bool ignore = false;
			if (s.get(c[1])) {
				if (c[1] == '\n' || c[1] == '\r') {
					if (s.get(c[2])) {
						if ((c[2] == '\n' || 
							c[2] == '\r') &&
							c[1] != c[2]) 
						{

						} else {
							s.putback(c[2]);
						}
					}
					this->line++;
					this->char_pos = 0;
					ignore = true;
				} else {
					s.putback(c[1]);
				}
			}
			if (!ignore) {
				translation3(c[0]);	
			}
		} else {
			translation3(c[0]);	
		}

		if (c[0] == '\n' || c[0] == '\r') {
			if (s.get(c[1])) {
				if ((c[1] == '\n' || c[1] == '\r') &&
					c[1] != c[0]) 
				{

				} else {
					s.putback(c[1]);
				}
			}
			this->line++;
			this->char_pos = 0;
		} else {
			this->char_pos++;
		}
	}

	translation3(0);
		
	this->line = line;
	this->char_pos = char_pos;
	this->file = file_;
}


void PreProcessor::check_pragma()
{
//	current = tokens.get_pragma_keyword();
	if (current.size() > 0) directive();
}

/* translation phase 4 */
void PreProcessor::directive()
{
	Env ev;
	string t = current.substr(1);
	current.clear();
	size_t i = 0;
	while (t[i] == ' ' || t[i] == '\t' || t[i] == '\v' || t[i] == '\f') i++;
	size_t p = i;
	switch (t[i]) {
	case 'i':
		if (t.compare(i, 7, "include") == 0) {
			p += 7;
			while (t[p] == ' ' || t[p] == '\t' || t[p] == '\v'
				|| t[p] == '\f')
			{
				p++;
			}
			if (t[p] == '"') {
				i = p + 1;
				while (t[i] != '"') i++;
				t = t.substr(p + 1, i - p - 1);
				environ.process_inc(make_unique<string>(t), true);
				return;
			} else if (t[p] == '<') {
				i = p + 1;
				while (t[i] != '>') i++;
				t = t.substr(p + 1, i - p - 1);
				environ.process_inc(make_unique<string>(t), false);
				return;
			} else {
				throw std::runtime_error("#" + t);
			}
		} else if (t.compare(i, 5, "ifdef") == 0) {
		} else if (t.compare(i, 6, "ifndef") == 0) {
		} else if (t.compare("if") == 0) {
		}
		break;
	case 'd':
		if (t.compare(i, 6, "define") == 0) {

		}
		break;
	case 'u':
		if (t.compare(i, 5, "undef", i) == 0) {

		}
		break;
	case 'e':
		if (t.compare(i, 4, "else", i) == 0) {
		} else if (t.compare(i, 4, "elif", i) == 0) {
		} else if (t.compare(i, 5, "endif", i) == 0) {
		} else if (t.compare(i, 5, "error", i) == 0) {
		}
		break;
	case 'l':
		if (t.compare(i, 4, "line", i) == 0) {
			throw std::runtime_error("#" + t);
		}
		break;
	case 'p':
		if (t.compare(i, 6, "pragma") == 0) {
		}
		break;
	}
	cout << current << "\n";
	return;
	PreProcessor pp(ev);
	pp.set_is_directive(true);
	istringstream s(t);
	pp.process(s, 0);
	current.clear();
}

/**
 * 5.1.1.2 Translation phases 3)
 * split the string into preprocessing tokens and replace comment by one
 * space character.
 */
void PreProcessor::translation3(char c)
{
	size_t l = current.size();
	string t;

	if (c == '#' && ((char_pos == 0 && l == 0) ||
		(cchar_pos == 0 && l > 0 && current.at(0) == ' '))) 
	{
		current = '#';
		return;
	} 

	if (l < 1) {
		switch (c) {
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\n':
		case '\r':
			current.push_back(' ');
			break;
		default:
			current.push_back(c);
			break;
		}
		cline = line; cchar_pos = char_pos;
		return;	
	}

	switch (current.at(0)) {
	case '#':
		if (is_directive) break;
		if (l > 2 && current.at(l - 2) == '/' && 
			current.at(l - 1) == '*') 
		{
			if (c == '*') {
				current.push_back(c);
				return;
			} else {
				return;
			}
		} else if (l > 3 && current.at(l - 3) == '/' && 
			current.at(l - 2) == '*' && current.at(l - 1) == '*')
		{
			if (c == '/') {
				current.resize(l - 3);
				current.push_back(' ');
				return;
			} else {
				current.resize(l - 1);
				return;
			}
		} 
		switch (c) {
		case '\r':
		case '\n':
			directive();
			break;
		case ' ':
		case '\t':
		case '\v':
		case '\f':
			if (l == 1) return;
		default:
			current.push_back(c);
			break;
		}
		return;
	}

	if (skip) return;

	switch (current.at(0)) {
	case '#':
		if (l == 1 && c == '#') {
			current.push_back(c);
			tokens.push(current, '#', file, cline, cchar_pos);
			current.clear();
			return;
		} else {
			tokens.push(current, '#', file, cline, cchar_pos);
			current.clear();
		}
		break;
	case '\'':
		if (l > 1 && c == '\'') {
			size_t k = 0;
			l--;
			while (current.at(l) == '\\') {
				k++;
				if (l == 0) break;
				l--;
			}
			if ((k & 1) == 0) {
				t = current.substr(1);
				tokens.push(t, '\'', file, cline, cchar_pos);
				current.clear();
				return;
			}
		} else if (c == '\'') {
			t = current.substr(1);
			tokens.push(t, '\'', file, cline, cchar_pos);
			current.clear();
			return;
		}
		break;
	case '"':
		if (c == '"') {
 			if (tokens.last_is_raw_string()) {
				if (l > 1 && current.at(l - 1) == ')') {
					t = current.substr(1);
					tokens.push(t, 
						'"', file, cline, cchar_pos);
					current.clear();
					return;
				}
			} else if (l > 1) {
				size_t k = 0;
				l--;
				while (current.at(l) == '\\') {
					l--;
					k++;
				}
				if ((k & 1) == 0) {
					t = current.substr(1);
					tokens.push(t, '"', file, 
						cline, cchar_pos);
					current.clear();
					return;
				}
			} else {
				t = current.substr(1);
				tokens.push(t, 
					'"', file, cline, cchar_pos);
				current.clear();
				return;
			}
		}
		break;
	case ' ':
	case '\t':
	case '\v':
	case '\f':
	case '\n':
	case '\r':
		switch (c) {
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\n':
		case '\r':
			return;
		}
		t = " ";
		tokens.push(t, ' ', file, cline, cchar_pos);
		current.clear();
		break;
	case '=':
		if (l == 1) {
			switch (c) {
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		}
		break;
	case '^':
		if (l == 1) {
			switch (c) {
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '|':
		if (l == 1) {
			switch (c) {
			case '=':
			case '|':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '&':
		if (l == 1) {
			switch (c) {
			case '=':
			case '&':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '%':
		if (l == 1) {
			switch (c) {
			case ':':
				current = '#';
				return;
			case '>':
				current.push_back(c);
				tokens.push(current, '}', file, cline, 
					cchar_pos);
				current.clear();
				return;
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '*':
		if (l == 1) {
			switch (c) {
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '<':
		if (l == 1) {
			switch (c) {
			case '<':
				break;
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			case '%':
				current.push_back(c);
				tokens.push(current, '{', file, cline, 
					cchar_pos);
				current.clear();
				return;
			case ':':
				current.push_back(c);
				tokens.push(current, '[', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		} else {
			if (c == '=') {
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			} else {
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		}
		break;
	case '>':
		if (l == 1) {
			switch (c) {
			case '>':
				break;
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		} else {
			if (c == '=') {
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			} else {
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		}	
		break;
	case '-':
		if (l == 1) {
			switch (c) {
			case '=':
			case '-':
			case '>':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
		}
		break;
	case '+':
		if (l == 1) {
			switch (c) {
			case '=':
			case '+':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
				
		}
		break;
	case '/':
		if (l == 1) {
			switch (c) {
			case '*':
			case '/':
				current.push_back(c);
				return;
			case '=':
				current.push_back(c);
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				tokens.push(current, '+', file, cline, 
					cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
				
			}
		} else if (current.at(1) == '*') {
			if (l == 3 && c == '/' && current.back() == '*') {
				t = " ";
				tokens.push(t, ' ', file, cline, cchar_pos);
				current.clear();
				return;
			} else if (l == 2) {
				current.push_back(c);
				return;
			} else {
				current.back() = c;
				return;
			}	
		} else if (current.at(1) == '/') {
			if (c == '\n' || c == '\r') {
				current = " ";
				return;
			}
		}
		break; 
	case ',':
		tokens.push(current, ',', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case '!':
		tokens.push(current, '+', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case ':':
		if (l == 1) {
			switch (c) {
			case '>':
				current.push_back(c);
				tokens.push(current, ']', file, 
					cline, cchar_pos);
				current.clear();
				return;
			case ':':
				current.push_back(c);
				tokens.push(current, ':', file, cline, 
					cchar_pos);
				current.clear();
				return;
			default:
				break;
			}
		}
		tokens.push(current, ':', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case '?':
		tokens.push(current, '?', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case '~':
		tokens.push(current, '+', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case '.':
		if (l == 1) {
			if (c == '.') {
				break;
			} else if (c >= '0' && c <= '9') {
				break;
			}
		} else {
			if (c == '.') {
				current.push_back(c);
				tokens.push(current, '.', file, 
					cline, cchar_pos);
				current.clear();
				return;
			} else if (((c >= '0' && c <= '9') || c == 'e' ||
				c == 'E' || 
					((current.at(l - 1) == 'e' ||
					current.at(l - 1) == 'E') && 
					(c == '-' || c == '+'))) &&
				current.at(1) >= '0' && current.at(1 <= '9')) 
			{
				break;
			}
		}
		tokens.push(current, '.', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case ';':
		tokens.push(current, ';', file, cline, cchar_pos);
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
		tokens.push(current, current.at(0), file, cline, cchar_pos);
		if (current.at(0) == ')') {
			check_pragma();
		}
		cline = line; cchar_pos = char_pos;
		current = c;
		return;
	default:
		switch (c) {
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\n':
		case '\r':
			c = ' ';
		case '\'':
		case '"':
			if (current.at(0) >= '0' && current.at(0) <= '9') {
				tokens.push(current, '1', file, cline, 
					cchar_pos);
			} else {
				tokens.push(current, 'a', file, cline, 
					cchar_pos);
			}
			cline = line; cchar_pos = char_pos;
			current = c;
			return;
		case ';':
		case ':':
		case '?':
		case '!':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case ',':
		case '+':
		case '-':
		case '=':
		case '*':
		case '/':
		case '%':
		case '&':
		case '|':
		case '^':
		case '<':
		case '>':
		case '~':
		case '#':
			if (current.at(0) >= '0' && current.at(0) <= '9') {
				if (current.at(l - 1) == 'e' || 
					current.at(l - 1) == 'E')
				{
					if (c == '-' || c == '+') break;
				}
				tokens.push(current, '1', file, 
					cline, cchar_pos);
			} else {
				tokens.push(current, 'a', file, 
					cline, cchar_pos);
			}
			cline = line; cchar_pos = char_pos;
			current = c;
			return;
		case '.':
			if (current.at(0) >= '0' && current.at(0) <= '9') {
				break;
			} else {
				tokens.push(current, 'a', file, 
					cline, cchar_pos);
				cline = line; cchar_pos = char_pos;
				current = c;
				return;
			}
			break;	
		default:
			break;
		}
		break;
	}
	current.push_back(c);
}

