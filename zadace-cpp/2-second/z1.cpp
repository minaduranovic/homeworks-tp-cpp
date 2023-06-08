// TP 2022/2023: Zadaća 2, Zadatak 1
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

bool vidljivi = true;
std::vector<std::vector<char>> mat(23,
                                   std::vector<char>(63, ' ')); // inic u mainu

enum class Pravci {
  Sjever,
  Sjeveroistok,
  Istok,
  Jugoistok,
  Jug,
  Jugozapad,
  Zapad,
  Sjeverozapad
};
enum class KodoviGresaka {
  PogresnaKomanda,
  NedostajeParametar,
  SuvisanParametar,
  NeispravanParametar
};
enum class Komande { Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj };

void Idi(int &x, int &y, Pravci orijentacija, int korak) {
  mat.at(11 - y).at(31 + x) = ' ';
  const std::array<std::array<int, 2>, 8> moguci = {{{{0, 1}},
                                                     {{1, 1}},
                                                     {{1, 0}},
                                                     {{1, -1}},
                                                     {{0, -1}},
                                                     {{-1, -1}},
                                                     {{-1, 0}},
                                                     {{-1, 1}}}};
  int pomx = moguci[static_cast<int>(orijentacija)][0];
  int pomy = moguci[static_cast<int>(orijentacija)][1];
  if (korak < 0) {
    pomx = -pomx;
    pomy = -pomy;
    korak = -korak;
  }
  for (int i = 0; i < korak; i++) {
    if (vidljivi) {
      mat.at(11 - y).at(31 + x)= '*';
    }
    x += pomx;
    y += pomy;

    if (x < -30)
      x = 30;
    else if (x > 30)
      x = -30;
    if (y < -10)
      y = 10;
    else if (y > 10)
      y = -10;
  }
  mat.at(11 - y).at(31 + x) = 'O';
}
void Rotiraj(Pravci &orijentacija, int ugao) {
  int nova = (static_cast<int>(orijentacija) - ugao) % 8;
  if (nova < 0)
    nova += 8;
  orijentacija = static_cast<Pravci>(nova);
}
void PostaviVidljivost(bool vidljiv) {
  if (vidljiv)
    vidljivi = true;
  else
    vidljivi = false;
}
void IspisiPoziciju(int x, int y, Pravci orijentacija) {
  std::vector<std::string> poz = {"sjever",    "sjeveroistok", "istok",
                                  "jugoistok", "jug",          "jugozapad",
                                  "zapad",     "sjeverozapad"};
  std::cout << "Robot je " << (vidljivi ? "vidljiv" : "nevidljiv")
            << ", nalazi se na poziciji (" << x << "," << y << ") i gleda na "
            << poz[static_cast<int>(orijentacija)] << ".\n";
}
void PrikaziTeren() {
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat.at(i).size(); j++) {
        if (i==0 || i==mat.size()-1 || j==0 || j==mat.at(i).size()-1) mat.at(i).at(j)='#';
      std::cout << mat.at(i).at(j);
    }
    std::cout << std::endl;
  }
}
void PrijaviGresku(KodoviGresaka kod_greske) {
  switch (kod_greske) {
  case KodoviGresaka::PogresnaKomanda:
    std::cout << "Nerazumljiva komanda!" << std::endl;
    break;
  case KodoviGresaka::NedostajeParametar:
    std::cout << "Komanda trazi parametar koji nije naveden!" << std::endl;
    break;
  case KodoviGresaka::NeispravanParametar:
    std::cout << "Parametar komande nije ispravan!" << std::endl;
    break;
  case KodoviGresaka::SuvisanParametar:
    std::cout << "Zadan je suvisan parametar nakon komande!" << std::endl;
    break;
  }
}
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija) {
  switch (komanda) {
  case Komande::Idi:
    Idi(x, y, orijentacija, parametar);
    break;
  case Komande::Rotiraj:
    Rotiraj(orijentacija, parametar);
    break;
  case Komande::Sakrij:
    PostaviVidljivost(false);
    break;
  case Komande::Otkrij:
    PostaviVidljivost(true);
    break;
  case Komande::PrikaziTeren:
    PrikaziTeren();
    break;
  case Komande::Kraj:
    break;
  }
}
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
  char znak;
  std::cin >> znak;
  switch (znak) {
  case 'I':
    komanda = Komande::Idi;
    if (std::cin >> parametar) {
      znak = std::cin.get();
      if (znak != ' ' && znak != '\n') {
        kod_greske = KodoviGresaka::NeispravanParametar;
        return false;
      }
    } else {
      kod_greske = KodoviGresaka::NedostajeParametar;
      return false;
    }
    break;
  case 'R':
    komanda = Komande::Rotiraj;
    if (std::cin >> parametar) {
      znak = std::cin.get();
      if (znak != ' ' && znak != '\n') {
        kod_greske = KodoviGresaka::NeispravanParametar;
      }
    } else {
      kod_greske = KodoviGresaka::NedostajeParametar;
      return false;
    }
    break;
  case 'S':
    znak = std::cin.get();
    if (znak == '+') {
      komanda = Komande::Sakrij;
    } else if (znak == '-') {
      komanda = Komande::Otkrij;
    } else {
      kod_greske = KodoviGresaka::PogresnaKomanda;
      return false;
    }
    break;
  case 'T':
    komanda = Komande::PrikaziTeren;
    break;
  case 'K':
    komanda = Komande::Kraj;
    break;
  default:
    kod_greske = KodoviGresaka::PogresnaKomanda;
    return false;
  }
  std::cin.clear();
  std::cin.ignore(1000, '\n');
  return true;
}
int main() {
int x=0,y=0;
Pravci orijentacija=Pravci::Sjever;
Komande komanda;
int parametar;
KodoviGresaka kod_greske;
IspisiPoziciju(x, y,  orijentacija);
while(true){
    std::cout<<"Unesi komandu: ";
    if (UnosKomande(komanda, parametar,kod_greske)){
        if (komanda==Komande::Kraj){
            std::cout<<"Dovidjenja!"<<std::endl;
            break;
        }
        IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
        IspisiPoziciju(x, y,orijentacija);
    }else{
        PrijaviGresku(kod_greske);
    }
}


  return 0;
}
