//TP 2022/2023: Zadaća 5, Zadatak 5
#include <iostream>
#include <cmath>
#include<functional>
#include<fstream>
#include <stdexcept>
#include<vector>
#include<algorithm>

template <typename TipElemenata>
 class DatotecniKontejner {
 std::fstream tok;
 public:
 DatotecniKontejner(const std::string &ime_datoteke);
 void DodajNoviElement(const TipElemenata &element);
 int DajBrojElemenata();
 TipElemenata DajElement(int pozicija);
 void IzmijeniElement(int pozicija, const TipElemenata &element);
 void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>
 kriterij = std::less<TipElemenata>());
 };
template<typename t>
 DatotecniKontejner<t>::DatotecniKontejner(const std::string &ime_datoteke) {
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
        if (!tok) {
            tok.clear();
            tok.open(ime_datoteke, std::ios::out);
            tok.close();
            tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
        }
        if (!tok)
            throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
    }
template<typename TipElemenata>
void DatotecniKontejner<TipElemenata>::DodajNoviElement(const TipElemenata &element) {
    tok.clear(); 
    tok.seekp(0, std::ios::end); 
    tok.write(reinterpret_cast<const char *>(&element), sizeof(element));
    if (!tok)
        throw std::logic_error("Problemi prilikom pristupa datoteci");
}

template<typename TipElemenata>
    int DatotecniKontejner<TipElemenata>::DajBrojElemenata() {
        tok.seekg(0, std::ios::end);
        return tok.tellg() / sizeof(TipElemenata);
    }
template<typename TipElemenata>
    TipElemenata DatotecniKontejner<TipElemenata>:: DajElement(int pozicija) {
        if (pozicija < 0 || pozicija >= DajBrojElemenata())
            throw std::range_error("Neispravna pozicija");
        TipElemenata element;
        tok.seekg(pozicija * sizeof(element), std::ios::beg);
        tok.read(reinterpret_cast<char *>(&element), sizeof(element));
        if (!tok)
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        return element;
    }
template<typename TipElemenata>
    void DatotecniKontejner<TipElemenata>::IzmijeniElement(int pozicija, const TipElemenata &element) {
        if (pozicija < 0 || pozicija >= DajBrojElemenata())
            throw std::range_error("Neispravna pozicija");
        tok.seekp(pozicija * sizeof(element), std::ios::beg);
        tok.write(reinterpret_cast<const char *>(&element), sizeof(element));
        if (!tok)
            throw std::logic_error("Problemi prilikom pristupa datoteci");
    }
template<typename TipElemenata>
void DatotecniKontejner<TipElemenata>::Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij) {
    int n = DajBrojElemenata();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            TipElemenata elem1 = DajElement(j);
            TipElemenata elem2 = DajElement(j + 1);
            if (kriterij(elem2, elem1)) {
                IzmijeniElement(j, elem2);
                IzmijeniElement(j + 1, elem1);
            }
        }
    }
}

int main ()
{
    try {
        DatotecniKontejner<int> kontejner("datoteka.dat");
        for (int i = 10; i >= 0; i--) {
            kontejner.DodajNoviElement(i);
        }
        std::cout << "Broj elemenata: " << kontejner.DajBrojElemenata() << std::endl;

        for (int i = 0; i < kontejner.DajBrojElemenata(); ++i) {
            std::cout << "Element na poziciji " << i << ": " << kontejner.DajElement(i) << std::endl;
        }

        kontejner.IzmijeniElement(5, 100);

        for (int i = 0; i < kontejner.DajBrojElemenata(); ++i) {
            std::cout << "Element na poziciji " << i << ": " << kontejner.DajElement(i) << std::endl;
        }

        kontejner.Sortiraj();
        for (int i = 0; i < kontejner.DajBrojElemenata(); ++i) {
            std::cout << "Element na poziciji " << i << ": " << kontejner.DajElement(i) << std::endl;
        }

    } catch (const std::exception &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    return 0;
}