#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<size_t nVal>
struct string_t {
    //const char(&directive)[nDir]
    const char(&val)[nVal];

    friend ostream& operator<<(ostream os, const string_t& inc) {
        return os << inc.val;
    }

    template<typename..TString>
    friend ostream& operator<<(ostream os, const tuple<TStrings...>& inc) {
        apply([&os](const auto&... args) { (os << args << '\n'), ...); }, inc);
        return os << inc.val;
    }
};

template<typename ...TStrings>
auto _base(TStrings... args) {
    return make_tuple(_base(args)...);
}

template<size_t n>
string_t<n> __test(const char(&header)[n]) {
    return _base("#include", header);
}

template<size_t n>
string_t<n> _test(const char(&header)[n]) {
    return { "test", header };
}

template<const char* t>
basic_ostream<char, char_traits<char>>& __cdecl test(basic_ostream<char, char_traits<char>>& os) {
    const char* tt = t;
    return os << tt;
}

//template<class _Elem, class _Traits>
//basic_ostream<char, char_traits<char>>& __cdecl ptr(basic_ostream<char, char_traits<char>>& os, string type, string id) {
//    os << type << "* " << id << ";";
//    return os;
//}

template<int n = 1>
basic_ostream<char, char_traits<char>>& _newline(basic_ostream<char, char_traits<char>>& os) {
    for (int i = 0; i < n; i++) {
        os << endl;
    }
    return os;
}

template<int n = 1>
basic_ostream<char, char_traits<char>>& __cdecl _tab(basic_ostream<char, char_traits<char>>& os) {
    for (int i = 0; i < n; i++) {
        os << "\t";
    }
    return os;
}

template<int n = 1>
basic_ostream<char, char_traits<char>>& __cdecl _space(basic_ostream<char, char_traits<char>>& os) {
    for (int i = 0; i < n; i++) {
        os << " ";
    }

    return os;
}

basic_ostream<char, char_traits<char>>& __cdecl _open_parenthesis(basic_ostream<char, char_traits<char>>& os) {
    return os << "(";
}

template<bool semicolon = true>
basic_ostream<char, char_traits<char>>& __cdecl _closing_parenthesis(basic_ostream<char, char_traits<char>>& os) {
    return os << ")" << (semicolon ? ";" : "");
}

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

basic_ostream<char, char_traits<char>>& __cdecl _virtual(basic_ostream<char, char_traits<char>>& os) {
    return os << "virtual" << _space;
}

basic_ostream<char, char_traits<char>>& __cdecl _pragma(basic_ostream<char, char_traits<char>>& os) {
    return os << "#pragma" << _space;
}

basic_ostream<char, char_traits<char>>& __cdecl _class(basic_ostream<char, char_traits<char>>& os) {
    return os << "class" << _space;
}

basic_ostream<char, char_traits<char>>& __cdecl _inherit(basic_ostream<char, char_traits<char>>& os) {
    return os << _space << ":" << _space;
}

basic_ostream<char, char_traits<char>>& __cdecl _include(basic_ostream<char, char_traits<char>>& os) {
    return os << "#include" << _space;
}

basic_ostream<char, char_traits<char>>& __cdecl _quote(basic_ostream<char, char_traits<char>>& os) {
    return os << "\"";
}

//basic_ostream<char, char_traits<char>>& operator ""_q(basic_ostream<char, char_traits<char>>&os) {
//
//}