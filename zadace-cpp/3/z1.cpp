// TP 2022/2023: Zadaća 3, Zadatak 1
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>


#define eps 1e-5
bool ekstr=false;
bool ekstr2=false;
bool cifra(char c) {
  if ((c >= '0' && c <= '9') || c=='.')
    return true;
  return false;
}

std::function<double(double)> LagrangeovaInterpolacija(
    const std::vector<std::pair<double, double>> &cvorovi) {
  double Xmin = cvorovi[0].first;
  double Xmax = cvorovi[0].first;
ekstr=false;
  for (int i = 0; i < cvorovi.size(); i++) {
    for (int j = i + 1; j < cvorovi.size(); j++) {
      if (std::fabs(cvorovi[i].first - cvorovi[j].first) < eps) {
        throw std::domain_error("Neispravni cvorovi");
      }
    }
    if (cvorovi[i].first < Xmin) {
      Xmin = cvorovi[i].first;
    }
    if (cvorovi[i].first > Xmax) {
      Xmax = cvorovi[i].first;
    }
  }

  return [=](double x) {
      ekstr=false;
    if (x < Xmin || x > Xmax) {

    ekstr=true;
    }
    double p = 0;
    for (int i = 0; i < cvorovi.size(); i++) {
      double l = 1;
      for (int j = 0; j < cvorovi.size(); j++) {
        if (i != j) {
          l *= (x - cvorovi[j].first) / (cvorovi[i].first - cvorovi[j].first);
        }
      }
      p += l * cvorovi[i].second;
    }
    return p;
  };
}

std::function<double(double)>
LagrangeovaInterpolacija(std::function<double(double)> funkcija, double Xmin,
                         double Xmax, double delta) {
ekstr=false;
  if (delta <= 0 || Xmax < Xmin) {
    throw std::domain_error("Nekorektni parametri");
  }

  int n = ((Xmax - Xmin) / delta) + 1;
  
  std::vector<std::pair<double, double>> cvorovi;
  for (int i = 0; i < n; i++) {
    double x = Xmin + i * delta;
    cvorovi.push_back({x, funkcija(x)});
  }

  return [=](double x) {

        if (x < Xmin || x > Xmax) {
    ekstr2=true;
    }
    double p = 0;
    for (int i = 0; i < cvorovi.size(); i++) {
      double l = cvorovi[i].second;
      for (int j = 0; j < cvorovi.size(); j++) {
        if (i != j) {
          l *= (x - cvorovi[j].first) / (cvorovi[i].first - cvorovi[j].first);
        }
      }
      p += l;
    }
    return p;
  };
}

int main() {
try{
  std::vector<std::pair<double, double>> cvorovi;

  int opcija;
  std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
  std::cin >> opcija;
  std::function<double(double)> f = [](double x) {
    return x * x + std::sin(x) + std::log(x + 1);
  }; 
   std::function<double(double)> funkcija; 
  if (opcija == 1) {
    int n;
    std::cout << "Unesite broj cvorova: ";
    std::cin >> n;
    std::cout << "Unesite cvorove kao parove x y: ";
    for (int i = 0; i < n; i++) {
      double x, y;
      std::cin >> x >> y;
      cvorovi.push_back({x, y});
    }
    std::string unos; 
     try {
        funkcija = LagrangeovaInterpolacija(cvorovi);
      } catch 
      
      (std::domain_error &e) {
        std::cout << e.what();
        return 1;
      }
    while (true) {
      std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      std::cin >> unos;
      if (unos=="kraj") break;
      bool validno = true;
      for (auto c : unos) {
        if (!cifra(c)) {
          validno = false;
          break;
        }
      }
      if (!validno)
        break;
      double x = std::stod(unos);
      double y;

    
      std::cout << "f(" << x << ") = " << funkcija(x);
      if (ekstr==true)  std::cout << " [ekstrapolacija]";
      std::cout << std::endl;
    }
  }

  else if (opcija == 2) {
    double x1, x2, korak;
    std::cout << "Unesite krajeve intervala i korak: ";
    std::cin >> x1 >> x2 >> korak;
    std::string unos;
  try{
      funkcija = LagrangeovaInterpolacija(f, x1, x2, korak);

   } catch (std::domain_error &e) {
        std::cout << e.what();
        return 1;
      }
    while (true) {
     std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      std::cin >> unos;
      if (unos=="kraj") break;
      bool validno = true;
      for (auto c : unos) {
        if (!cifra(c)) {
          validno = false;
          break;
        }
      }
      if (!validno)
        break;
      double x = std::stod(unos);
      
    //   try {    
   
      std::cout << "f(" << x << ") = " << f(x) << " P(" << x
                << ") = " << funkcija(x);
                if (ekstr2==true) std::cout<<" [ekstrapolacija]";
      std::cout << std::endl;
    }
  }
}catch(std::domain_error &e){
    std::cout<<e.what();
}
  // auto P = LagrangeovaInterpolacija({{1, 3}, {2, 5}, {4, 4}, {5, 2}, {7,
  // 1}}); std::cout<<P(0.3);

  return 0;
}
