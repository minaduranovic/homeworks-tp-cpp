// TP 2022/2023: Zadaća 1, Zadatak 1
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

int MultiplikativniDigitalniKorijen(long long int broj, long long int baza) {

  if (broj < 0)
    broj = -broj;
  if (baza < 2)
    throw std::domain_error("Neispravna baza");

  while (broj >= baza) {
    long long int tren = 1;
    while (broj > 0) {
      tren *= broj % baza;
      broj /= baza;
    }
    broj = tren;
  }
  return broj;
}
std::array<std::vector<long long int>, 10>
RazvrstajBrojeve(std::vector<long long int> elementi, TretmanNegativnih izbor) {
  std::array<std::vector<long long int>, 10> rezult;

  for (int i = 0; i < elementi.size(); i++) {
    if (elementi.at(i) < 0 && izbor == TretmanNegativnih::PrijaviGresku) {
      throw std::domain_error(
          "Nije predvidjeno razvrstavanje negativnih brojeva");
    } else if (elementi.at(i) < 0 &&
               izbor == TretmanNegativnih::IgnorirajZnak) {
      elementi.at(i) = -elementi.at(i);
    } else if (elementi.at(i) < 0 && izbor == TretmanNegativnih::Odbaci) {
      continue;
    }

    int korijen = MultiplikativniDigitalniKorijen(elementi.at(i), 10);
    rezult.at(korijen).push_back(elementi.at(i));
  }

  return rezult;
}
int main() {
 
  long long int broj;
  std::vector<long long int> brojevi;
  std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";

  for (;;) {
    std::cin >> broj;
    if (std::cin) {
      brojevi.push_back(broj);
    } else if (!std::cin) {
      break;
    }
  }
  for (int i = 0; i < brojevi.size(); i++) {
    if (brojevi.at(i) < 0) {
      std::cout << "Nije podrzano razvrstavanje negativnih brojeva!";
      return 0;
    }
  }
  try {
    std::array<std::vector<long long int>, 10> rezultat =
        RazvrstajBrojeve(brojevi, TretmanNegativnih::PrijaviGresku);
    std::cout
        << std::endl
        << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu: ";
    for (int i = 0; i <= 9; i++) {
      if (rezultat.at(i).size() == 0) {
        continue;
      }
      std::cout << i << ": ";
      for (int j = 0; j < rezultat.at(i).size(); j++) {
        if (j >= rezultat.at(i).size())
          continue;
        std::cout << rezultat.at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error &e) {
    std::cout << std::endl << "GRESKA: " << e.what();
  }
  return 0;
}
