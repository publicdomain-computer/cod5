#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace std;

class Prod;

class Elem {
public:
	Elem(string v, Prod *p, int r, int c) {
		value = v;
		row = r;
		prod = p;
		column = c;
		parent = nullptr;
		conflict = false;
	}

	string value;
	Elem *parent;
	Prod *prod;
	int row;
	int column;
	bool conflict;
	vector<Elem *> follow_set;
};

class Prod {
public:
	Prod(int t)
	{
		type = t;
		first_added = true;
		first_set.clear();
	}

	~Prod()
	{

	}

	void new_first(string f, Elem *parent, int row)
	{
		if (parent && parent->prod == this) {
			return;
		}
		for (auto &&i: first_set) {
			if (i->value == f && i->prod == this && i->parent == parent) {
				return;
			}

		}
		Elem *ne = new Elem(f, this, row, 0);
		ne->parent = parent;
		first_set.push_back(ne);

		first_added = true;
	}

	void check_first(const string &pa)
	{
		for (unsigned int i = 0; i < pr.size(); i++) {
			if (pr[i].size() < 1) continue;
			string s = pr[i][0]->value;
			if (s.length() < 1) continue;
			//cout << s << s.rfind("-opt") << endl;

			if (s.rfind("-opt") == s.length() - 4) {
				s = s.substr(0, s.length() - 4);
			}
			//cout << "'" << s << "'" << endl;
			if (all.at(s)->type == 0) {
				new_first(s, nullptr, i);
			} else {
				int sq = all.at(s)->first_set.size();
				for (int i = 0; i < sq; i++) {
					new_first(all.at(s)->first_set[i]->value,
						  all.at(s)->first_set[i], i);
				}
			}
		}
	}

	void expand_opt()
	{
		unsigned int i = 0;
		int si = pr.size();
		bool expanded = true;
		while (expanded) {
			expanded = false;
			for (; i < si; i++) {
				vector<Elem*> &line = pr[i];
				for (int j = 0; j < line.size(); j++) {
					Elem *e = line[j];
					string &s = e->value;
					if (s.length() > 4 && s.rfind("-opt") == s.length() - 4) {
						e->value = s.substr(0, s.length() - 4);
						vector<Elem*> v;
						for (int k = 0; k < line.size(); k++) {
							if (k != j) {
								v.push_back(new Elem(line[k]->value,
									this, pr.size(), v.size()));
							}
						}
						if (v.size() > 0) {
							pr.push_back(v);
						} else {
							v.push_back(new Elem("no-token", this, pr.size(), 0));
							pr.push_back(v);

						}
						expanded = true;
						break;
					}
				}
				if (expanded) break;

			}
			i = 0;
			si = pr.size();
		}
	}

	Elem *get_next(Elem *e) {
		Elem *r = nullptr;
		if (e->parent) {
			r = get_next(e->parent);
			if (r) return r;
		}
		if (e->row < e->prod->pr.size() && e->prod->pr[e->row].size() > (e->column + 1)) {
			r = e->prod->pr[e->row][e->column + 1];
		}
		return r;
	}

	void check_follow()
	{
		for (Elem *it: first_set) {
			Elem *e = get_next(it);
			if (e) {
				if (all[e->value]->type != 0) {
					for (auto &&k: all[e->value]->first_set) {
						bool dont_set = false;
						for (auto &&l: it->follow_set) {
							if (l->value == k->value) {
								dont_set = true;
								break;
							}
						}
						if (!dont_set) it->follow_set.push_back(k);
					}
				} else {
					it->follow_set.push_back(e);
				}
			} else {
				it->follow_set.push_back(new Elem("no-token", this, it->row, it->column + 1));
			}
		}
	}

	bool first_added;

	vector<Elem *> first_set;


	int type;
	static std::map<std::string, Prod*> all;

	vector<vector<Elem*>> pr;
};

std::map<std::string, Prod*> Prod::all;

const vector<Elem*> explode(const string& s, const char& c, Prod *prod, int row)
{
	string buf("");
	vector<Elem*> v;
	int col = 0;
	for (auto n: s)
	{
		if (n != c && n != '\t') {
			buf += n;
		} else {
			if (n == c && buf != "") {
				Elem *m = new Elem(buf, prod, row, col);
				v.push_back(m);
				buf = "";
			}
		}
	}
	if(buf != "") {
		Elem *m = new Elem(buf, prod, row, col);
		v.push_back(m);
	}
	return v;
}

int main()
{
	ifstream is;
	is.open("../cod5-0.1/doc/keyword.txt", ifstream::in);
	string s;
	while (getline(is, s)) {
		if (s.length() < 1) continue;
		Prod::all[s] = new Prod(0);
	}

	is.close();
	is.open("../cod5-0.1/doc/grammar.txt", ifstream::in);
	string cur;
	while (getline(is, s)) {
		if (s.length() < 2) continue;
		if (s.find_last_of(':') == s.length() - 1 && s[0] != '\t') {
			s = s.substr(0, s.length() - 1);
			if (s.length() < 1) continue;
			Prod::all[s] = new Prod(1);
			cur = s;
		} else {
			auto spl = explode(s, ' ', Prod::all[cur], Prod::all[cur]->pr.size());
			Prod::all[cur]->pr.push_back(spl);
			for (auto &&i: spl) {
				if ((i->value[0] >= 0x21  && i->value[0] <= 0x2F) ||
					(i->value[0] >= 0x5B  && i->value[0] <= 0x5E) ||
					(i->value[0] >= 0x7B  && i->value[0] <= 0x7E) ||
					(i->value[0] >= 0x3A  && i->value[0] <= 0x40)
					)
				{
					if (i->value.rfind("-opt") == i->value.length() - 4) {
						string t = i->value.substr(0, i->value.length() - 4);
						if (t.length() < 1) continue;
						Prod::all[t] = new Prod(0);
					} else {
						if (i->value.length() < 1) continue;
						Prod::all[i->value] = new Prod(0);
						//cout << i << endl;
					}
				}
			}
		}
	}

	for (auto &&it : Prod::all) {
		it.second->expand_opt();
	}

	for (auto &&it : Prod::all) {
		if (it.second->type == 0) {
			cout << it.first << endl;
		}
	}
	cout << endl;

	for (auto &&it : Prod::all) {
		if (it.second->type == 0) {
			continue;
		}
		cout << it.first << ":" << endl;

		for (auto && p: it.second->pr) {
			cout << "\t";
			for (auto &&q: p) {
				cout << q->value << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool done = false;
	while (!done) {
		done = true;
		for (auto &&it : Prod::all) {
			it.second->first_added = false;
		}
		for (auto &&it : Prod::all) {
			it.second->check_first(it.first);
			if (it.second->first_added) {
				done = false;
			}
		}
	}


	for (auto &&it : Prod::all) {
		it.second->check_follow();
	}


	cout << endl;
	for (auto &&it : Prod::all) {
		if (it.second->type == 0) {
			continue;
		}

		cout <<  "=== " << it.first << " === " << it.second->pr.size() << endl;
		for (auto &&i: it.second->pr) {
			//cout << " " << i[0] << endl;
		}
		map<string,int> b;
		map<string, vector<Elem *>> f;
		for (auto &&i: it.second->first_set) {
			b[i->value]++;
			//cout << " " << i->value << endl;
			bool add = true;
			for (auto &&j: i->follow_set) {
				add = true;
				bool con = false;
				for (auto &&k: f[i->value]) {
					if (k->value == j->value) {
						if (k->prod == j->prod) {
							add = false;
						} else {
							con = true;
						}
					}
				}
				if (add) {
					if (con) {
						Elem *e = new Elem(j->value, j->prod, j->row, j->column);
						e->parent = j->parent;
						e->conflict = true;
						f[i->value].push_back(e);
					} else {
						f[i->value].push_back(j);
					}
				}
			}

			for (auto &&j: i->follow_set) {
				//cout << "   " << j->value << endl;
			}
		}
		for (auto i: f) {
			cout << " " << i.first << endl;
			for (auto &&k: i.second) {
				cout << "    " << k->value << "  conf" << k->conflict << endl;
			}
		}
		cout << endl;
	}

	return 0;
}

