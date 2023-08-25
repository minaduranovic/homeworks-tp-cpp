// TP 2022/2023: Zadaća 4, Zadatak 3
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

// klasa POLAZAK
class Polazak {
  std::string odrediste;
  std::string oznaka_voznje;
  int broj_perona;
  int sat_polaska;
  int minute_polaska;
  int trajanje_voznje;
  int kasnjenje;
  
  

public:
  Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona,
          int sat_polaska, int minute_polaska, int trajanje_voznje);

  void PostaviKasnjenje(int kasnjenje) {
    if (kasnjenje < 0)
      throw std::logic_error("Neregularna vrijednost kasnjenja");
    this->kasnjenje = kasnjenje;
  }
  bool DaLiKasni() const {
    if (!kasnjenje)
      return false;
    return true;
  }
  int DajTrajanje() const { return trajanje_voznje; }

  void OcekivanoVrijemePolaska(int &sati, int &minute) const;

  void OcekivanoVrijemeDolaska(int &sati, int &minute) const;

  void Ispisi() const;
};
void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const {
  int ukupno = (sat_polaska * 60) + minute_polaska + kasnjenje;
  sati = (ukupno / 60) % 24;
  minute = ukupno % 60;
}

void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const {
  int ukupno =
      (sat_polaska * 60) + minute_polaska + kasnjenje + trajanje_voznje;
  sati = (ukupno / 60) % 24;
  minute = ukupno % 60;
}
void Polazak::Ispisi() const {
  std::cout << std::setw(10) << std::left << oznaka_voznje;
  std::cout << std::setw(30) << std::left << odrediste;

  if (kasnjenje == 0) {
    int a, b;
    OcekivanoVrijemeDolaska(a, b);
    std::cout << std::setw(10) << std::right << std::setfill(' ')
              << std::setw(2) << sat_polaska << ":" << std::setfill('0')
              << std::setw(2) << minute_polaska << std::setfill(' ') << " ";
    std::cout << std::setw(10) << std::right << std::setfill(' ')
              << std::setw(2) << a << ":" << std::setfill('0') << std::setw(2)
              << b << std::setfill(' ') << " ";
    std::cout << std::setw(8) << std::right << broj_perona;
  };
  if (kasnjenje > 0) {
    int s, m;
    OcekivanoVrijemePolaska(s, m);
    std::cout << std::setw(10) << std::right << std::setfill(' ')
              << std::setw(2) << s << ":" << std::setfill('0') << std::setw(2)
              << m << std::setfill(' ') << " ";

    std::cout << " (Planirano " << std::setfill(' ') << std::setw(2)
              << sat_polaska << ":" << std::setfill('0') << std::setw(2)
              << minute_polaska << ", Kasni " << std::setfill(' ') << kasnjenje
              << " min)";
  }

  std::cout << std::endl;
}

Polazak::Polazak(std::string odrediste, std::string oznaka_voznje,
                 int broj_perona, int sat_polaska, int minute_polaska,
                 int trajanje_voznje)
    : kasnjenje(0) {
  if (broj_perona < 1 || broj_perona > 15 || sat_polaska < 0 ||
      sat_polaska > 23 || minute_polaska < 0 || minute_polaska > 59 ||
      trajanje_voznje < 0) {
    throw std::domain_error("Neispravni podaci");
  }
  Polazak::odrediste = odrediste;
  Polazak::oznaka_voznje = oznaka_voznje;
  Polazak::broj_perona = broj_perona;
  Polazak::sat_polaska = sat_polaska;
  Polazak::minute_polaska = minute_polaska;
  Polazak::trajanje_voznje = trajanje_voznje;
}
class Polasci {
  int max_br_polazaka;
  int br_polazaka;
  Polazak **polasci;
void sortiranje (){

}
public:
  explicit Polasci(int max_broj_polazaka)
      : max_br_polazaka(max_broj_polazaka), br_polazaka(0),
        polasci(new Polazak *[max_broj_polazaka]) {}
  Polasci(std::initializer_list<Polazak> lista_polazaka);
  ~Polasci();
  Polasci(const Polasci &polasci);
  Polasci(Polasci &&polasci);
  Polasci &operator=(const Polasci &polasci);
  Polasci &operator=(Polasci &&polasci);
  void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje);
  void RegistrirajPolazak(Polazak *polazak);
  int DajBrojPolazaka() const { return br_polazaka; };
  int DajBrojPolazakaKojiKasne() const;
  Polazak &DajPrviPolazak();
Polazak DajPrviPolazak() const;
Polazak &DajPosljednjiPolazak();
Polazak DajPosljednjiPolazak() const;
  void Ispisi() const;
  void IsprazniKolekciju();
  };
Polazak &Polasci::DajPrviPolazak() { auto x=std::min_element(polasci, polasci + br_polazaka,
            [](const Polazak *p1, const Polazak *p2) {
              int sati1, minute1, sati2, minute2;
              p1->OcekivanoVrijemePolaska(sati1, minute1);
              p2->OcekivanoVrijemePolaska(sati2, minute2);
              return (sati1 < sati2) || (sati1 == sati2 && minute1 < minute2);
            }); return **x; }
  Polazak Polasci::DajPrviPolazak() const { auto x=std::min_element(polasci, polasci + br_polazaka,
            [](const Polazak *p1, const Polazak *p2) {
              int sati1, minute1, sati2, minute2;
              p1->OcekivanoVrijemePolaska(sati1, minute1);
              p2->OcekivanoVrijemePolaska(sati2, minute2);
              return (sati1 < sati2) || (sati1 == sati2 && minute1 < minute2);
            }); return **x; }
  Polazak &Polasci::DajPosljednjiPolazak() { auto x=std::max_element(polasci, polasci + br_polazaka,
            [](const Polazak *p1, const Polazak *p2) {
              int sati1, minute1, sati2, minute2;
              p1->OcekivanoVrijemePolaska(sati1, minute1);
              p2->OcekivanoVrijemePolaska(sati2, minute2);
              return (sati1 < sati2) || (sati1 == sati2 && minute1 < minute2);
            }); return **x; }
  Polazak Polasci:: DajPosljednjiPolazak() const {auto x=std::max_element(polasci, polasci + br_polazaka,
            [](const Polazak *p1, const Polazak *p2) {
              int sati1, minute1, sati2, minute2;
              p1->OcekivanoVrijemePolaska(sati1, minute1);
              p2->OcekivanoVrijemePolaska(sati2, minute2);
              return (sati1 < sati2) || (sati1 == sati2 && minute1 < minute2);
            }); return **x; }


Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka)
    : max_br_polazaka(lista_polazaka.size()),
      br_polazaka(lista_polazaka.size()),
      polasci(new Polazak *[lista_polazaka.size()]) {
  int i = 0;
  for (auto polazak : lista_polazaka) {
    polasci[i] = new Polazak(polazak);
    i++;
  }
}
Polasci::Polasci(const Polasci &polasci)
    : max_br_polazaka(polasci.max_br_polazaka),
      br_polazaka(polasci.br_polazaka),
      polasci(new Polazak *[polasci.max_br_polazaka]) {
  for (int i = 0; i < br_polazaka; i++) {
    Polasci::polasci[i] = new Polazak(*(polasci.polasci[i]));
  }
}
Polasci &Polasci::operator=(const Polasci &polasci) {
  if (&polasci != this) {
    Polazak **novi = new Polazak *[polasci.max_br_polazaka];
    for (int i = 0; i < polasci.br_polazaka; i++) {
      novi[i] = new Polazak(*(polasci.polasci[i]));
    }
    IsprazniKolekciju();
    max_br_polazaka = polasci.max_br_polazaka;
    br_polazaka = polasci.br_polazaka;
    Polasci::polasci = novi;
  }
  return *this;
}
Polasci::Polasci(Polasci &&polasci)
    : max_br_polazaka(polasci.max_br_polazaka),
      br_polazaka(polasci.br_polazaka), polasci(polasci.polasci) {
  polasci.polasci = nullptr;
}
Polasci &Polasci::operator=(Polasci &&polasci) {
  if (&polasci != this) {
    max_br_polazaka = polasci.max_br_polazaka;
    br_polazaka = max_br_polazaka;
    Polasci::polasci = polasci.polasci;
    polasci.polasci = nullptr;
  }
  return *this;
}Polasci::~Polasci() {
for (int i = 0; i < br_polazaka; i++) {
    delete polasci[i];
}
  delete[] polasci;
  polasci=nullptr;
  br_polazaka=0;
}
void Polasci::IsprazniKolekciju() {
    if (polasci==nullptr) return;
  for (int i = 0; i < br_polazaka; i++) {
    delete polasci[i];
  }
  br_polazaka = 0;
}
void Polasci::Ispisi() const {
  //   std::cout << std::left << std::setw(10) << "Voznja";
  //   std::cout << std::left << std::setw(30) << "Odrediste";
  //   std::cout << std::left << std::setw(10) << "Polazak";
  //   std::cout << std::left << std::setw(10) << "Dolazak";
  //   std::cout << std::left << std::setw(8) << "Peron";
  //   std::cout << std::endl;
  std::cout << "    Voznja                     Odrediste   Polazak   Dolazak   "
               "Peron\n--------------------------------------------------------"
               "--------------\n";

  std::sort(polasci, polasci + br_polazaka,
            [](const Polazak *p1, const Polazak *p2) {
              int sati1, minute1, sati2, minute2;
              p1->OcekivanoVrijemePolaska(sati1, minute1);
              p2->OcekivanoVrijemePolaska(sati2, minute2);
              return (sati1 < sati2) || (sati1 == sati2 && minute1 < minute2);
            });
  for (int i = 0; i < br_polazaka; i++) {
    polasci[i]->Ispisi();
  }
}
void Polasci::RegistrirajPolazak(std::string odrediste,
                                 std::string oznaka_voznje, int broj_perona,
                                 int sat_polaska, int minute_polaska,
                                 int trajanje_voznje) {
  if (br_polazaka >= max_br_polazaka)
    throw std::range_error("Maksimalan broj polazaka");

  polasci[br_polazaka] =
      new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska,
                  minute_polaska, trajanje_voznje);
  br_polazaka++;
}
void Polasci::RegistrirajPolazak(Polazak *polazak) {
  if (br_polazaka >= max_br_polazaka)
    throw std::range_error("Dostignut maksimalan broj polazaka");
  polasci[br_polazaka] = polazak;
  br_polazaka++;
}
int Polasci::DajBrojPolazakaKojiKasne() const {
  return std::count_if(polasci, polasci + br_polazaka,
                       [](const Polazak *p) { return p->DaLiKasni(); });
}

int main() { 

  Polasci polasci(5);

  polasci.RegistrirajPolazak("Sarajevo", "V1", 1, 10, 30, 120);
  polasci.RegistrirajPolazak("Mostar", "M3", 3, 12, 15, 90);
  polasci.RegistrirajPolazak("Zenica", "Z5", 2, 14, 0, 60);
  polasci.RegistrirajPolazak("Tuzla", "T2", 1, 16, 45, 75);
  polasci.RegistrirajPolazak("Banja Luka", "B7", 4, 18, 30, 105);

  std::cout << "Broj polazaka: " << polasci.DajBrojPolazaka() << std::endl;
  std::cout << "Broj polazaka koji kasne: "
            << polasci.DajBrojPolazakaKojiKasne() << std::endl;

  std::cout << "Prvi: ";
  polasci.DajPrviPolazak().Ispisi();

  std::cout << "Posljednji: ";
  polasci.DajPosljednjiPolazak().Ispisi();

  std::cout << "Ispis s:" << std::endl;
  polasci.Ispisi();

  polasci.IsprazniKolekciju();


    return 0; }
