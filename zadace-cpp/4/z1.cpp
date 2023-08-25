// TP 2022/2023: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <utility>
#include <vector>


// #define eps 1e-11
 constexpr double eps=1e-10;
// KLASA
class Krug {
  std::pair<double, double> c;
  double r;
  
static bool priblizno(double a, double b){
    return std::abs(a-b)<=eps*(std::abs(a)+std::abs(b));
}
public:
  explicit Krug(double poluprecnik = 0) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    r = poluprecnik;
    c.first = 0;
    c.second = 0;
  }
  explicit Krug(const std::pair<double, double> &centar,
                double poluprecnik = 0) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    r = poluprecnik;
    c.second = centar.second;
    c.first = centar.first;
  }
  std::pair<double, double> DajCentar() const { return c; }
  double DajPoluprecnik() const { return r; }
  double DajObim() const { return 2 * r * 4 * std::atan(1); }
  double DajPovrsinu() const { return r * r * 4 * std::atan(1); }
  Krug &PostaviCentar(const std::pair<double, double> &centar) {
    c.first = centar.first;
    c.second = centar.second;
    return *this;
  }
  Krug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    r = poluprecnik;
    return *this;
  }
  Krug &Transliraj(double delta_x, double delta_y) {
  c.first += delta_x;
  c.second += delta_y;
  return *this;
}

Krug &Rotiraj(double alpha) {
  double x = c.first * cos(alpha) - c.second * sin(alpha);
  double y = c.first * sin(alpha) + c.second * cos(alpha);
  c=std::make_pair(x, y);
  return *this;
}

void Ispisi() const {
  std::cout << "{(" << c.first << "," << c.second << ")," << r << "}";//novi red
}
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                double alpha) {
    double x= centar_rotacije.first + ((c.first - centar_rotacije.first) * cos(alpha)) - ((c.second - centar_rotacije.second) * sin(alpha));
    double y= centar_rotacije.second + ((c.first - centar_rotacije.first) * sin(alpha)) + ((c.second - centar_rotacije.second) * cos(alpha));
    c = std::make_pair(x, y);
    return *this;
  }
  static double RastojanjeCentara(const Krug &k1, const Krug &k2) {
    return std::sqrt(std::pow(k1.c.first-k2.c.first,2)+ std::pow(k1.c.second-k2.c.second,2));
  }
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2) {
   return priblizno(k1.r, k2.r)&& priblizno(k1.c.first, k2.c.first)&& priblizno(k1.c.second, k2.c.second);
  }
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2) {
   return priblizno(k1.r, k2.r);
  }
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2) {
  return priblizno(k1.c.first, k2.c.first)&& priblizno(k1.c.second, k2.c.second);
  }
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {
   return priblizno(RastojanjeCentara(k1,k2), k1.r+k2.r);
  }
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
    return priblizno(std::abs(k1.r-k2.r), RastojanjeCentara(k1, k2));
  }
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2) {
   return RastojanjeCentara(k1, k2)<(k1.r+k2.r) ;////priblizno
  }
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2) {
    double d = RastojanjeCentara(k1, k2);
    return (d > std::abs(k1.r-k2.r))&& (d<(k1.r+k2.r));
  }
  bool DaLiSadrzi(const Krug &k) const {
    return (RastojanjeCentara(*this, k)+k.r)<this->r|| priblizno(RastojanjeCentara(*this, k)+k.r, this->r);
  }
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {
    Krug novi = k;
    novi.Transliraj(delta_x, delta_y);
    return novi;
  }
  friend Krug RotiraniKrug(const Krug &k, double alpha) {
    Krug novi = k;
    novi.Rotiraj(alpha);
    return novi;
  }
  friend Krug RotiraniKrug(const Krug &k,
                           const std::pair<double, double> &centar_rotacije,
                           double alpha) {
    Krug novi;
    novi.Rotiraj(centar_rotacije, alpha);
    return novi;
  }
};

int main() {
    int n;
  std::cout << "Unesite broj krugova: ";
  std::cin >> n;
    if (n<=0){
std::cout<<"\nUneseni broj nije prirodan!";
return 1;
    } 
  std::vector<Krug*> nizKrugova(n);

  for (int i = 0; i < n; i++) {
double x,y,r;

while(true){
    std::cout << "Unesite centar " << i + 1 << ". kruga: ";
    std::cin >> x>> y;
if (!std::cin ){
    std::cout<<"Neispravne koordinate centra! Pokusajte ponovo: \n\n";
    std::cin.clear();
    std::cin.ignore(1000,'\n');
}else{

    std::cout << "Unesite poluprecnik " << i + 1 << ". kruga: ";
    std::cin >>r;
    if(!std::cin ||r<0){
        std::cout<<"Neispravan poluprecnik! Pokusajte ponovo: \n\n";
        std::cin.clear();
        std::cin.ignore(1000,'\n');
    }else break;
}}
    try {
      nizKrugova[i] = new Krug(std::make_pair(x, y), r);
    } catch (std::domain_error& e) {
      std::cout << e.what() << std::endl;
      std::cout << "Ponovite unos za " << i + 1 << ". krug." << std::endl;
      i--;
    }
  
  }
  double delta_x, delta_y;
  std::cout << "Unesite parametre translacije (delta_x,delta_y): ";
  std::cin >> delta_x >> delta_y;

  double ugao;
  std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
  std::cin >> ugao;
  double alpha = ugao * 4*atan(1)/ 180.0;  

  std::transform(nizKrugova.begin(), nizKrugova.end(), nizKrugova.begin(),
                 [delta_x, delta_y](Krug* krug) {
                   (*krug).Transliraj(delta_x, delta_y);
                   return krug;
                 });

  std::transform(nizKrugova.begin(), nizKrugova.end(), nizKrugova.begin(),
                 [alpha](Krug* krug) {
                   (*krug).Rotiraj(alpha);
                   return krug;
                 });

  std::sort(nizKrugova.begin(), nizKrugova.end(),
            [](Krug* krug1, Krug* krug2) {
              return (*krug1).DajPovrsinu() < (*krug2).DajPovrsinu();
            });
  std::cout << "Parametri krugova nakon obavljene transformacije su: \n";
  std::for_each(nizKrugova.begin(),nizKrugova.end(),
                  [](const Krug *k) {
                    k->Ispisi();
                    std::cout<<std::endl;
                  });
  std::cout<<"Krug sa najvecim obimom je: ";
auto max = std::max_element(nizKrugova.begin(), nizKrugova.end(), [](const Krug* k1, const Krug* k2) {
    return k1->DajObim() < k2->DajObim();
});

if (max != nizKrugova.end()) {
    (*max)->Ispisi();
}
std::cout<<std::endl;
std::vector<std::pair<Krug*, Krug*>> presjecajuci;
for(auto it1 = nizKrugova.begin(); it1 != nizKrugova.end(); ++it1) {
    for(auto it2 = std::next(it1); it2 != nizKrugova.end(); ++it2) {
        Krug* k1 = *it1;
        Krug* k2 = *it2;
        if (Krug::DaLiSeSijeku(*k1, *k2) || Krug::DaLiSeDodirujuIznutri(*k1, *k2) || Krug::DaLiSeDodirujuIzvani(*k1, *k2)) {
            std::pair<Krug*, Krug*> pair = std::make_pair(k1, k2);
            if (std::find(presjecajuci.begin(), presjecajuci.end(), pair) == presjecajuci.end()) {
                presjecajuci.push_back(pair);
            }
        }
    }
}

if (presjecajuci.size()!=0) {
    std::for_each(presjecajuci.begin(), presjecajuci.end(), [](const std::pair<Krug*, Krug*>& par) {
        std::cout << "Presjecaju se krugovi: \n";
        par.first->Ispisi();
        std::cout << " i ";
        par.second->Ispisi();
        std::cout << std::endl;
    });
} else {
    std::cout << "Ne postoje krugovi koji se presjecaju!";
}

  for (int i = 0; i < n; i++) {
    delete nizKrugova[i];
  }

  return 0;
}

