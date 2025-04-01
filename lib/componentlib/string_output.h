#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <functional>

using namespace std;

string _quote(const char* value) {
    return "\"" + string(value) + "\"";
}

string _quote(string value) {
    return "\"" + value + "\"";
}

template<size_t N>
string _quote(const char(&value)[N]) {
    return "\"" + string(value) + "\"";
}

string _angles(const char* value) {
    return "<" + string(value) + ">";
}

string _angles(string value) {
    return "<" + string(value) + ">";
}

string _new(string value) {
    return "new " + value + "();";
}

string _new(string value, string ctorArgs) {
    return "new " + value + "(" + ctorArgs + ");";
}

struct string_t {
private:
    vector<string>  strings;

public:
    string_t(char del, initializer_list<string> init) : strings(init) {}
    string_t(initializer_list<string> list) : strings(list) {}
    string_t(string s) : strings{ s } {}

    friend ostream& operator<<(ostream& os, const string_t& dir) {
        for (auto& it = dir.strings.begin(); it != dir.strings.end(); it++) {
            os << string(*it);
        }

        return os;
    }

    operator string() {
        ostringstream os;
        for (auto& it = strings.begin(); it != strings.end(); it++) {
            os << string(*it);
        }

        return os.str();
    }
};

template<typename... TStrings>
ostream& operator<<(ostream& os, const tuple<TStrings...>& args) {
    apply([&os](const auto&... args) { ((os << args << '\n'), ...); }, args);
    return os;
}

template<size_t N, bool semi = true>
string_t _call(const char(&value)[N]) {
    return { value, "()", (semi ? ";" : "") };
}

string_t _call(string value, bool semi = true) {
    return { value, "()", (semi ? ";" : "")};
}

string_t _call(string value, string params, bool semi = true) {
    return { value, "(", params, ")", (semi ? ";" : "") };
}

string_t _var(string type, string ident, string value = "") {
    return { type, " ", ident, (value.empty() ? ";" : string(" = " + value + ";"))};
}

string_t _func_decl(string specs, string id, string args = "") {
    return { specs, " ", id, "(" + (args.empty() ? "" : args) + ");"};
}

string_t _func_def(string specs, string id, string body = "") {
    return { specs, " ", id, "()", " ", (body.empty() ? "{}" : body)};
}

string_t _virtual(string value) {
    return { "virtual ", value };
}

string_t _include(string value, bool sys = false) {
    return { "#include ", (sys ? _angles(value) : _quote(value)) };
}

template<size_t N>
string_t _pragma(const char(&value)[N]) {
    return { "#pragma ",  value};
}

template<size_t N>
string_t _class(const char(&value)[N]) {
    return { "class ", value };
}

string_t _class(string value) {
    return { "class ", value };
}

template<size_t aN, size_t vN>
string_t _inherit(const char(&access)[aN], const char(&value)[vN]) {
    return { " : ", access, " ", value};
}

template<size_t N>
string_t _inherit(const char(&access)[N], string value) {
    return { " : ", access, value };
}

//string_t _include(string value, bool sys = false) {
//    return _include(value.c_str(), sys);
//}

template<size_t N = 1>
ostream& _newline(ostream& os) {
    return os << string(N, '\n');
}

template<size_t N = 1>
ostream& _tab(ostream& os) {
    return os << string(N, '\t');
}

template<size_t N = 1>
ostream& _space(ostream& os) {
    return os << string(N, '\s');
}

ostream& _open_parenthesis(ostream& os) {
    return os << string("(");
}

template<bool semicolon = true>
ostream& __cdecl _closing_parenthesis(ostream& os) {
    return os << ")" << (semicolon ? ";" : "");
}

//template<int n = 1>
//basic_ostream<char, char_traits<char>>& _newline(basic_ostream<char, char_traits<char>>& os) {
//    for (int i = 0; i < n; i++) {
//        os << endl;
//    }
//    return os;
//}

//template<int n = 1>
//basic_ostream<char, char_traits<char>>& __cdecl _tab(basic_ostream<char, char_traits<char>>& os) {
//    for (int i = 0; i < n; i++) {
//        os << "\t";
//    }
//    return os;
//}

//template<int n = 1>
//basic_ostream<char, char_traits<char>>& __cdecl _space(basic_ostream<char, char_traits<char>>& os) {
//    for (int i = 0; i < n; i++) {
//        os << " ";
//    }
//
//    return os;
//}

//basic_ostream<char, char_traits<char>>& __cdecl _open_parenthesis(basic_ostream<char, char_traits<char>>& os) {
//    return os << "(";
//}

//template<bool semicolon = true>
//basic_ostream<char, char_traits<char>>& __cdecl _closing_parenthesis(basic_ostream<char, char_traits<char>>& os) {
//    return os << ")" << (semicolon ? ";" : "");
//}

template<bool semicolon = true>
basic_ostream<char, char_traits<char>>& __cdecl _openclose_parenthesis(basic_ostream<char, char_traits<char>>& os) {
    return os << "()" << (semicolon ? ";" : "");
}

basic_ostream<char, char_traits<char>>& __cdecl _open_bracket(basic_ostream<char, char_traits<char>>& os) {
    return os << " {";
}

template<bool semicolon = true>
basic_ostream<char, char_traits<char>>& __cdecl _closing_bracket(basic_ostream<char, char_traits<char>>& os) {
    return os << "}" << (semicolon ? ";" : "");
}

template<bool semicolon = true>
basic_ostream<char, char_traits<char>>& __cdecl _openclose_brackets(basic_ostream<char, char_traits<char>>& os) {
    return os << "{}" << (semicolon ? ";" : "");
}

//basic_ostream<char, char_traits<char>>& __cdecl _virtual(basic_ostream<char, char_traits<char>>& os) {
//    return os << "virtual" << _space;
//}

//basic_ostream<char, char_traits<char>>& __cdecl _pragma(basic_ostream<char, char_traits<char>>& os) {
//    return os << "#pragma" << _space;
//}
//
//basic_ostream<char, char_traits<char>>& __cdecl _class(basic_ostream<char, char_traits<char>>& os) {
//    return os << "class" << _space;
//}
//
//basic_ostream<char, char_traits<char>>& __cdecl _inherit(basic_ostream<char, char_traits<char>>& os) {
//    return os << _space << ":" << _space;
//}

//basic_ostream<char, char_traits<char>>& __cdecl _include(basic_ostream<char, char_traits<char>>& os) {
//    return os << "#include" << _space;
//}

basic_ostream<char, char_traits<char>>& __cdecl _quote(basic_ostream<char, char_traits<char>>& os) {
    return os << "\"";
}

//basic_ostream<char, char_traits<char>>& operator ""_q(basic_ostream<char, char_traits<char>>&os) {
//
//}