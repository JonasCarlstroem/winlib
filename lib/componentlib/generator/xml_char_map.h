#include <xercesc/util/XMLChar.hpp>
#include <unordered_map>

using namespace xercesc;
using namespace std;

typedef unordered_map<char, XMLCh> xml_char_map;

//static const auto a = chLatin_a;
//static const auto b = chLatin_b;
//static const auto c = chLatin_c;
//static const auto d = chLatin_d;
//static const auto e = chLatin_e;
//static const auto f = chLatin_f;
//static const auto g = chLatin_g;
//static const auto h = chLatin_h;
//static const auto i = chLatin_i;
//static const auto j = chLatin_j;
//static const auto k = chLatin_k;
//static const auto l = chLatin_l;
//static const auto m = chLatin_m;
//static const auto n = chLatin_n;
//static const auto o = chLatin_o;
//static const auto p = chLatin_p;
//static const auto q = chLatin_q;
//static const auto r = chLatin_r;
//static const auto s = chLatin_s;
//static const auto t = chLatin_t;
//static const auto u = chLatin_u;
//static const auto v = chLatin_v;
//static const auto w = chLatin_w;
//static const auto x = chLatin_x;
//static const auto y = chLatin_y;
//static const auto z = chLatin_z;
//static const auto A = chLatin_A;
//static const auto B = chLatin_B;
//static const auto C = chLatin_C;
//static const auto D = chLatin_D;
//static const auto E = chLatin_E;
//static const auto F = chLatin_F;
//static const auto G = chLatin_G;
//static const auto H = chLatin_H;
//static const auto I = chLatin_I;
//static const auto J = chLatin_J;
//static const auto K = chLatin_K;
//static const auto L = chLatin_L;
//static const auto M = chLatin_M;
//static const auto N = chLatin_N;
//static const auto O = chLatin_O;
//static const auto P = chLatin_P;
//static const auto Q = chLatin_Q;
//static const auto R = chLatin_R;
//static const auto S = chLatin_S;
//static const auto T = chLatin_T;
//static const auto U = chLatin_U;
//static const auto V = chLatin_V;
//static const auto W = chLatin_W;
//static const auto X = chLatin_X;
//static const auto Y = chLatin_Y;
//static const auto Z = chLatin_Z;
//static const auto colon = chColon;
//
//static xml_char_map char_map = { 
//    { 'a', a },
//    { 'b', b },
//    { 'c', c },
//    { 'd', d },
//    { 'e', e },
//    { 'f', f },
//    { 'g', g },
//    { 'h', h },
//    { 'i', i },
//    { 'j', j },
//    { 'k', k },
//    { 'l', l },
//    { 'm', m },
//    { 'n', n },
//    { 'o', o },
//    { 'p', p },
//    { 'q', q },
//    { 'r', r },
//    { 's', s },
//    { 't', t },
//    { 'u', u },
//    { 'v', v },
//    { 'w', w },
//    { 'x', x },
//    { 'A', A },
//    { 'B', B },
//    { 'C', C },
//    { 'D', D },
//    { 'E', E },
//    { 'F', F },
//    { 'G', G },
//    { 'H', H },
//    { 'I', I },
//    { 'J', J },
//    { 'K', K },
//    { 'L', L },
//    { 'M', M },
//    { 'N', N },
//    { 'O', O },
//    { 'P', P },
//    { 'Q', Q },
//    { 'R', R },
//    { 'S', S },
//    { 'T', T },
//    { 'U', U },
//    { 'V', V },
//    { 'W', W },
//    { 'X', X },
//    { 'Y', Y },
//    { 'Z', Z },
//    { ':', colon }
//};