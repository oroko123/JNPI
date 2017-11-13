#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

typedef pair<unsigned int, unsigned int> years;
typedef tuple<unsigned int, string, float, string, string> stamp;
typedef vector<stamp> slist;

namespace {
    float to_float(const string &s) {
        static const regex comma(",");

        string new_s = regex_replace(s, comma, ".$2");

        return stof(new_s);
    }

    void add_stamp(const stamp &s, slist &stamps) { stamps.push_back(s); }

    void input_error(const string &line, int line_nr) {
        cerr << "Error in line " << line_nr << ":" << line << endl;
    }

    bool valid_query(const string &line, years &query) {
        smatch m;

        static const string out_whitespace_str = "\\s*";
        static const string year_str = "([1-2]\\d{3})";
        static const string whitespace_str = "\\s+";

        static const regex input(out_whitespace_str + year_str + whitespace_str +
                                 year_str + out_whitespace_str);

        regex_match(line, m, input);

        if (!m[0].matched) {
            return false;
        }

        int beg = stoi(m[1]);
        int end = stoi(m[2]);

        query = make_pair(beg, end);

        return beg <= end;
    }

    void sprint(const stamp &s) {
        static const int YEAR = 0;
        static const int NAME = 1;
        static const int POST = 3;
        static const int PRICE_REP = 4;

        cout << get<YEAR>(s) << " " << get<NAME>(s) << " " << get<PRICE_REP>(s) << " "
             << get<POST>(s) << endl;
    }

    void print_stamps(const years &yrs, slist &stamps) {
        vector<stamp>::iterator beg, end;
        stamp low(yrs.first, "", 0, "", "");
        stamp up(yrs.second + 1, "", 0, "", "");
        stamps.begin();

        beg = lower_bound(stamps.begin(), stamps.end(), low);
        end = upper_bound(stamps.begin(), stamps.end(), up);

        for_each(beg, end, sprint);
    }

    void get_stamp(const string &line, int line_nr, slist &stamps) {
        smatch m;

        static const string out_whitespace_str = "\\s*";
        static const string year_str = "([1-2]\\d{3})";
        static const string name_str = "(\\S.*\\S)";
        static const string whitespace_str = "\\s+";
        static const string price_str = "(\\d+((\\.|,)\\d+)?)";
        static const string post_str = "(\\S.*\\S)";

        static const regex whitespace(whitespace_str);
        static const regex input(out_whitespace_str + name_str + whitespace_str +
                                 price_str + whitespace_str + year_str +
                                 whitespace_str + post_str + out_whitespace_str);

        regex_match(line, m, input);

        if (m[0].matched) {
            string name = regex_replace(m[1].str(), whitespace, " $2");
            string price_s = m[2];
            int year = stoi(m[5]);
            string post = regex_replace(m[6].str(), whitespace, " $2");
            float price = to_float(price_s);

            stamp s(year, post, price, name, price_s);

            add_stamp(s, stamps);
        } else {
            input_error(line, line_nr);
        }
    }

    void get_query(const string &line, int line_nr, slist &stamps) {
        years query = make_pair(0, 0);

        if (valid_query(line, query)) {
            print_stamps(query, stamps);
        } else {
            input_error(line, line_nr);
        }
    }
}

int main() {
    slist stamps;
    string new_line;
    unsigned int line_nr = 0;
    years query(0, 0);

    while (getline(cin, new_line) && !valid_query(new_line, query)) {
        line_nr++;
        get_stamp(new_line, line_nr, stamps);
    }

    sort(stamps.begin(), stamps.end());

    line_nr++;
    print_stamps(query, stamps);

    while (getline(cin, new_line)) {
        line_nr++;
        get_query(new_line, line_nr, stamps);
    }

    return 0;
