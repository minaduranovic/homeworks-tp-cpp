// TP 2022/2023: Zadaća 1, Zadatak 2
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include<iomanip>

int veci(int a, int b) {
  if (a > b)
    return a;
  return b;
}
int manji(int a, int b) {
  if (a < b)
    return a;
  return b;
}
std::vector<std::vector<double>>
UsrednjavajuciFilter(std::vector<std::vector<double>> matrica, int n) {

  int broj_redova = matrica.size();
  int broj_kolona, count = 0;
  std::vector<std::vector<double>> nova(broj_redova, std::vector<double>());
  double sum = 0;
  if (n < 0)
    throw std::domain_error("Neispravan red filtriranja");

  for (int i = 0; i < broj_redova; i++) {
    broj_kolona = matrica.at(i).size();
    nova.at(i).resize(broj_kolona);
    for (int j = 0; j < matrica.at(i).size(); j++) {
      sum = 0;
      count = 0;

      for (int p = veci(0, i - n); p <= manji(broj_redova - 1, i + n); p++) {
        for (int q = veci(0, j - n); q <= manji(matrica.at(p).size()- 1, j + n);
             q++) {
                 if (  q<matrica.at(p).size() && p<broj_redova){
          sum += matrica.at(p).at(q);
          count++;
                 }
        }
      }
      nova.at(i).at(j) = sum / count;
    }
  }
  return nova;
}
int main() {
  int m=0, n=0;
  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> m >> n;
  std::vector<std::vector<double>> matrica(m, std::vector<double>(n));

  std::cout << "Unesite elemente matrice: ";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrica.at(i).at(j);
    }
  }
  int red;
  std::cout << "Unesite red filtriranja: ";
  std::cin >> red;

  try {
    auto nova = UsrednjavajuciFilter(matrica, red);
    std::cout<<std::endl<<"Matrica nakon filtriranja: "<<std::endl;
    for (int i = 0; i < nova.size(); i++) {
    for (int j = 0; j < nova.at(i).size(); j++) {
      std::cout << std::fixed<< std::setprecision(2)<< std::setw(7)<<nova.at(i).at(j);
    }
    std::cout<<std::endl;
  }
  } catch (std::domain_error &e) {
    std::cout << std::endl<<"GRESKA: " << e.what()<<'!';
  }
   
  return 0;
}
