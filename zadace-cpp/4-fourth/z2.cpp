// TP 2022/2023: Zadaća 4, Zadatak 2
#include <algorithm>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

constexpr double eps = 1e-10;

typedef std::pair<double, double> Centar;

// KLASA
class NepreklapajuciKrug {
  std::pair<double, double> c;
  double r;
  NepreklapajuciKrug *preth;
  static NepreklapajuciKrug *posl;
  static bool priblizno(double a, double b) {
    return std::abs(a - b) <= eps * (std::abs(a) + std::abs(b));
  }
  void preklapa() {
    NepreklapajuciKrug *tren = posl;
    while (tren != nullptr) {
      if (tren != this && (RastojanjeCentara(*this, *tren) < (r + tren->r)) ||
          priblizno(RastojanjeCentara(*this, *tren), (r + tren->r)))
        throw std::logic_error("Nedozvoljeno preklapanje");
      tren = tren->preth;
    }
  }

public:
  NepreklapajuciKrug(const NepreklapajuciKrug &k) = delete;
  NepreklapajuciKrug &operator=(const NepreklapajuciKrug &k) = delete;

  ~NepreklapajuciKrug() {
    if (posl == this)
      posl = preth;

    if (preth)
      preth->posl = posl;

    if (posl)
      posl->preth = preth;
  }
  explicit NepreklapajuciKrug(double poluprecnik = 0) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    r = poluprecnik;
    c.first = 0;
    c.second = 0;
    preth = posl;
    preklapa();
    posl = this;
  }
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar,
                              double poluprecnik = 0) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    r = poluprecnik;
    c.second = centar.second;
    c.first = centar.first;
    preth = posl;
    preklapa();
    posl = this;
  }
  std::pair<double, double> DajCentar() const { return c; }
  double DajPoluprecnik() const { return r; }
  double DajObim() const { return 2 * r * 4 * std::atan(1); }
  double DajPovrsinu() const { return r * r * 4 * std::atan(1); }

  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar) {

    auto x = c;
    c = centar;
    try {
      preklapa();
    } catch (...) {
      c = x;
      throw;
    }

    return *this;
  }
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    auto stari = r;
    r = poluprecnik;
    try {
      preklapa();
    } catch (...) {
      r = stari;
      throw;
    }

    return *this;
  }
  void Ispisi() const {
    std::cout << "{(" << c.first << "," << c.second << ")," << r << "}\n";
  }
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y) {
    auto stari = c;

    c.first += delta_x;
    c.second += delta_y;
    try {
      preklapa();
    } catch (...) {
      c = stari;
      throw;
    }
    return *this;
  }

  NepreklapajuciKrug &Rotiraj(double alpha) {
    alpha = alpha * 4 * atan(1) / 180.0;
    auto stari = c;
    double x = c.first * cos(alpha) - c.second * sin(alpha);
    double y = c.first * sin(alpha) + c.second * cos(alpha);
    c = std::make_pair(x, y);
    try {
      preklapa();
    } catch (...) {
      c = stari;
      throw;
    }
    return *this;
  }

  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                              double alpha) {
    alpha = alpha * 4 * atan(1) / 180.0;
    auto stari = c;
    double x = centar_rotacije.first +
               ((c.first - centar_rotacije.first) * cos(alpha)) -
               ((c.second - centar_rotacije.second) * sin(alpha));
    double y = centar_rotacije.second +
               ((c.first - centar_rotacije.first) * sin(alpha)) +
               ((c.second - centar_rotacije.second) * cos(alpha));
    c = std::make_pair(x, y);
    try {
      preklapa();
    } catch (...) {
      c = stari;
      throw;
    }
    return *this;
  }

  static double RastojanjeCentara(const NepreklapajuciKrug &k1,
                                  const NepreklapajuciKrug &k2) {
    return std::sqrt(std::pow(k1.c.first - k2.c.first, 2) +
                     std::pow(k1.c.second - k2.c.second, 2));
  }
};
NepreklapajuciKrug *NepreklapajuciKrug::posl = nullptr;
int main() {
  int n;
  std::cout << "Unesite broj krugova: ";
  while (true) {
    std::cin >> n;
    if (n > 0) {
      break;
    }
    std::cout << "Neispravan broj krugova, unesite ponovo!" << std::endl;
  }
  std::vector<std::shared_ptr<NepreklapajuciKrug>> niz;
  for (int i = 0; i < n; i++) {
    std::cout << "Unesite centar za " << i + 1 << ". krug: ";
    double x, y, r;
    bool prek = false;
    while (true) {
      if (!(std::cin >> x >> y)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Neispravan centar!" << std::endl;
        std::cout << "Unesite ponovo centar za " << i + 1 << ". krug: ";
      } else {
        std::cout << "Unesite poluprecnik: ";
        while (true) {
          if (!(std::cin >> r) || r < 0) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Neispravan poluprecnik!" << std::endl;
            std::cout << "Unesite ponovo poluprecnik za " << i + 1
                      << ". krug: ";
          } else {
            break;
          }
        }
        break;
      }
    }
    try {
      auto krug = std::make_shared<NepreklapajuciKrug>(std::make_pair(x, y), r);
      niz.push_back(std::move(krug));

    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      i--;
    }
  }
  std::cout << "Krugovi nakon obavljenog sortiranja: \n";
  std::sort(niz.begin(), niz.end(),
                   [](const std::shared_ptr<NepreklapajuciKrug> &p1,
                      const std::shared_ptr<NepreklapajuciKrug> &p2) {
                          if (p1.get()->DajPovrsinu()>p2.get()->DajPovrsinu() || p1.get()->DajPovrsinu()<p2.get()->DajPovrsinu())
                     return p1.get()->DajPovrsinu() > p2.get()->DajPovrsinu();
                     else if (p1.get()->DajCentar().first<p2.get()->DajCentar().first)return p1.get()->DajCentar().first<p2.get()->DajCentar().first;
                     else return  p1.get()->DajCentar().second>p2.get()->DajCentar().second;
                   });

  for (const auto &x : niz) {
    x->Ispisi();
  }

  return 0;
}
