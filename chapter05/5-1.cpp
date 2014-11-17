#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <tuple>
// #include "split.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::list;

list<string> split_by_space(const string& s)
{
	list<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters `['original value of `i', `i)'
	while (i != s.size()) {
		// ignore leading blanks
		// invariant: characters in range `['original `i', current `i)' are all spaces
		while (i != s.size() && isspace(s[i]))
			++i;

		// find end of next word
		string_size j = i;
		// invariant: none of the characters in range `['original `j', current `j)' is a space
		while (j != s.size() && !isspace(s[j]))
			++j;

		// if we found some nonwhitespace characters
		if (i != j) {
			// copy from `s' starting at `i' and taking `j' `\-' `i' chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}

	}
	return ret;
}

// move first string to the end
string reassemble(list<string>& ori_str_vec)
{
	string ping_me;

	list<string>::iterator iter;
	for(iter = ori_str_vec.begin(); iter != ori_str_vec.end(); ++iter)
	{
		ping_me += ' ' + (*iter);
	}
	return ping_me;
}

vector<string> rotate_lines(vector<string>& original_lines)
{
	vector<string> new_vec;
	vector<string>::iterator iter;
	for(iter = original_lines.begin(); iter != original_lines.end(); ++iter)
	{
		list<string> splited_line;
		splited_line = split_by_space(*iter);

		size_t counter = 0, total = splited_line.size();
		// reassemble string
		splited_line.push_back("\\");

		do
		{
			new_vec.push_back(reassemble(splited_line));
			string assembled;
			string temp = splited_line.front();
			splited_line.pop_front();
			splited_line.push_back(temp);

			++counter;
		}while(counter != total);
	}

	return new_vec;
}

std::vector<string> split_by_char(const string& s)
{
	typedef string::size_type string_size;
	string_size i = 0;
	vector<string> m_res;

	// invariant: we have processed characters `['original value of `i', `i)'
	while (i != s.size())
	{
		// ignore leading blanks
		// invariant: characters in range `['original `i', current `i)' are all spaces
		while (i != s.size() && isspace(s[i]))
			++i;

		// find end of next word
		string_size j = i;
		// invariant: none of the characters in range `['original `j', current `j)' is a space
		while (j != s.size() && s[j] != '\\')
			++j;

		// if we found some nonwhitespace characters
		if (i != j)
		{
			// copy from `s' starting at `i' and taking `j' `\-' `i' chars
			m_res.push_back(s.substr(i, j-i));
			m_res.push_back(s.substr(j+1, s.size()));
			// i = j;
			return m_res;
		}
	}
	return m_res;
}

void output(vector<string>& f_vec)
{
	vector<string>::iterator iter;
	for(iter = f_vec.begin(); iter != f_vec.end(); ++iter)
	{
		if ((*iter).find("\\") != string::npos)
		{
			// replace back slash
			vector<string> cols = split_by_char((*iter));
			cout << std::setw(30) << cols[0];
			cout << '\t' << cols[1] << endl;
		}
		else
		{
			cout << (*iter) << endl;
		}
	}
}

int main()
{
	string line;
	vector<string> m_vec, shuffled_vec;

	while(getline(cin, line))
	{
		m_vec.push_back(line);
	}

	// step 1:
	shuffled_vec = rotate_lines(m_vec);

	// step 2:
	sort(shuffled_vec.begin(), shuffled_vec.end());

	// step 3: output and split
	output(shuffled_vec);
	return 0;
}