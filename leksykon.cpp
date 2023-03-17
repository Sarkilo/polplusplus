// A simple Leksykon meant to demonstrate a few theoretical concepts. It can
// support several parser concepts and is very fast (though speed is not its
// design goal).
//
// J. Arrieta, Nabla Zero Labs
//
// This code is released under the MIT License.
//
// Copyright 2018 Nabla Zero Labs
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish ,distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string>


class Token {
 public:
  enum class Typ {
    Liczba,
    Identyfikator,
    OtwierajacyNawias,
    ZamykajacyNawias,
    OtwierajacyNawiasKwadratowy,
    ZamykajacyNawiasKwadratowy,
    OtwierajacyNawiasKlamrowy,
    ZamykajacyNawiasKlamrowy,
    MniejNiz,
    WiecejNiz,
    Rowny,
    Plus,
    Minus,
    Gwiazdka,
    Ukosnik,
    Hasztag,
    Kropka,
    Przecinek,
    Dwukropek,
    Srednik,
    Apostrof,
    Cudzyslow,
    Komentarz,
    KreskaPionowa,
    Koniec,
    Nieoczekiwany,
    Spacja,
    NowaLinia,
    Tabulator,
    PrzesuniecieKursoraDoLewej,
    ZnakZapytania,
  };

  Token(Typ typ) noexcept : m_typ{typ} {}

  Token(Typ typ, const char* beg, std::size_t len) noexcept
      : m_typ{typ}, m_leksem(beg, len) {}

  Token(Typ typ, const char* beg, const char* end) noexcept
      : m_typ{typ}, m_leksem(beg, std::distance(beg, end)) {}

  Typ typ() const noexcept { return m_typ; }

  void typ(Typ typ) noexcept { m_typ = typ; }

  bool jest(Typ typ) const noexcept { return m_typ == typ; }

  bool nie_jest(Typ typ) const noexcept { return m_typ != typ; }

  bool jest_jednym_z(Typ k1, Typ k2) const noexcept { return jest(k1) || jest(k2); }

  template <typename... Ts>
  bool jest_jednym_z(Typ k1, Typ k2, Ts... ks) const noexcept {
    return jest(k1) || jest_jednym_z(k2, ks...);
  }

  std::string_view leksem() const noexcept { return m_leksem; }

  void leksem(std::string_view leksem) noexcept {
    m_leksem = std::move(leksem);
  }

 private:
  Typ             m_typ{};
  std::string_view m_leksem{};
};

class Leksykon {
 public:
  Leksykon(const char* beg) noexcept : m_beg{beg} {}

  Token nastepny() noexcept;

 private:
  Token identyfikator() noexcept;
  Token liczba() noexcept;
  Token ukosnik_lub_komentarz() noexcept;
  Token atom(Token::Typ) noexcept;

  char zerknij() const noexcept { return *m_beg; }
  char zdobadz() noexcept { return *m_beg++; }

  const char* m_beg = nullptr;
};

bool czy_spacja(char c) noexcept {
  switch (c) {
    case ' ':
      return true;
    default:
      return false;
  }
}

bool czy_nowa_linia(char c) noexcept {
  switch (c) {
    case '\n':
      return true;
    default:
      return false;
  }
}

bool czy_tabulator(char c) noexcept {
  switch (c) {
    case '\t':
      return true;
    default:
      return false;
  }
}

bool czy_cyfra(char c) noexcept {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return true;
    default:
      return false;
  }
}

bool czy_z_ulamkiem_dziesietnym(char c) noexcept {
    switch(c) {
        case '.':
            return true;
        default:
            return false;
    }
}

bool czy_znak_identyfikatora(char c) noexcept {
  switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '_':
      return true;
    default:
      return false;
  }
}

Token Leksykon::atom(Token::Typ typ) noexcept { return Token(typ, m_beg++, 1); }

Token Leksykon::nastepny() noexcept {
//  while (czy_spacja(zerknij())) zdobadz();

  switch (zerknij()) {
    case '\0':
      return Token(Token::Typ::Koniec, m_beg, 1);
    default:
      return atom(Token::Typ::Nieoczekiwany);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
      return identyfikator();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return liczba();
    case '(':
      return atom(Token::Typ::OtwierajacyNawias);
    case ')':
      return atom(Token::Typ::ZamykajacyNawias);
    case '[':
      return atom(Token::Typ::OtwierajacyNawiasKwadratowy);
    case ']':
      return atom(Token::Typ::ZamykajacyNawiasKwadratowy);
    case '{':
      return atom(Token::Typ::OtwierajacyNawiasKlamrowy);
    case '}':
      return atom(Token::Typ::ZamykajacyNawiasKlamrowy);
    case '<':
      return atom(Token::Typ::MniejNiz);
    case '>':
      return atom(Token::Typ::WiecejNiz);
    case '=':
      return atom(Token::Typ::Rowny);
    case '+':
      return atom(Token::Typ::Plus);
    case '-':
      return atom(Token::Typ::Minus);
    case '*':
      return atom(Token::Typ::Gwiazdka);
    case '/':
      return ukosnik_lub_komentarz();
    case '#':
      return atom(Token::Typ::Hasztag);
    case '.':
      return atom(Token::Typ::Kropka);
    case ',':
      return atom(Token::Typ::Przecinek);
    case ':':
      return atom(Token::Typ::Dwukropek);
    case ';':
      return atom(Token::Typ::Srednik);
    case '\'':
      return atom(Token::Typ::Apostrof);
    case '"':
      return atom(Token::Typ::Cudzyslow);
    case '|':
      return atom(Token::Typ::KreskaPionowa);
    case ' ':
      return atom(Token::Typ::Spacja);
    case '\r':
      return atom(Token::Typ::Tabulator);
    case '\t':
      return atom(Token::Typ::PrzesuniecieKursoraDoLewej);
    case '\n':
      return atom(Token::Typ::NowaLinia);
    case '?':
      return atom(Token::Typ::ZnakZapytania);
  }
}

#include <iostream>
#include <list>

std::list<Token::Typ> lista_elementow_w_leksykonie = {};

Token Leksykon::identyfikator() noexcept {
  const char* start = m_beg;
  zdobadz();
  while (czy_znak_identyfikatora(zerknij())) zdobadz();
  return Token(Token::Typ::Identyfikator, start, m_beg);
}

Token Leksykon::liczba() noexcept {
  const char* start = m_beg;
  zdobadz();
  while (czy_cyfra(zerknij()) || czy_z_ulamkiem_dziesietnym(zerknij())) zdobadz();
  return Token(Token::Typ::Liczba, start, m_beg);
}

Token Leksykon::ukosnik_lub_komentarz() noexcept {
  const char* start = m_beg;
  zdobadz();
  if (zerknij() == '/') {
    zdobadz();
    start = m_beg;
    while (zerknij() != '\0') {
      if (zdobadz() == '\n') {
        return Token(Token::Typ::Komentarz, start, std::distance(start, m_beg) - 1);
      }
    }
    return Token(Token::Typ::Nieoczekiwany, m_beg, 1);
  } else {
    return Token(Token::Typ::Ukosnik, start, 1);
  }
}

#include <iomanip>


std::ostream& operator<<(std::ostream& os, const Token::Typ& typ) {
  static const char* const names[]{
      "Liczba",      "Identyfikator",  "OtwierajacyNawias",  "ZamykajacyNawias", "OtwierajacyNawiasKwadratowy",
      "ZamykajacyNawiasKwadratowy", "OtwierajacyNawiasKlamrowy",   "ZamykajacyNawiasKlamrowy", "MniejNiz",   "WiecejNiz",
      "Rowny",       "Plus",        "Minus",      "Gwiazdka",   "Ukosnik",
      "Hasztag",        "Kropka",         "Przecinek",      "Dwukropek",      "Srednik",
      "Apostrof", "Cudzyslow", "Komentarz",    "KreskaPionowa",       "Koniec",
      "Nieoczekiwany", "Spacja", "NowaLinia", "PrzesuniecieKursoraDoLewej", "Tabulator", "ZnakZapytania"
  };
  return os << names[static_cast<int>(typ)];
}



int leksykowanie(const char* kod) {
  // auto code =
  //     "x = 2\n"
  //     "// This is a comment.\n"
  //     "This is divide 4/2/2\n"
  //     "To jest kreska pionowa | | | \n"
  //     "var x\n"
  //     "var y\n"
  //     "var f = function(x, y) { sin(x) * sin(y) + x * y; }\n"
  //     "der(f, x)\n"
  //     "var g = function(x, y) { 2 * (x + der(f, y)); } // der(f, y) is a "
  //     "matrix\n"
  //     "var r{3}; // Vector of three elements\n"
  //     "var J{12, 12}; // Matrix of 12x12 elements\n"
  //     "var dot = function(u{:}, v{:}) -> scalar {\n"
  //     "\treturn u[i] * v[i]; // Einstein notation\n"
  //     "}\n"
  //     "var norm = function(u{:}) -> scalar { return sqrt(dot(u, u)); }\n"
  //     "tutaj jest przesuniecie kursora do lewej \r"
  //     "<end>";

  Leksykon lex(kod);
  for (auto token = lex.nastepny();
       not token.jest(Token::Typ::Koniec);
       token = lex.nastepny()) {
    lista_elementow_w_leksykonie.push_front(token.typ());
    std::cout << std::setw(28) << token.typ() << " |" << token.leksem() << "|\n";
  }

  return 0;
}
