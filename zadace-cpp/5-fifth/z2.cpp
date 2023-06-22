//TP 2022/2023: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include<vector>
#include <algorithm>
#include <functional>

class Padavine{
    std::vector<int> padavine;
    int maxKol;
    public:
    explicit Padavine(int maxKolicina){
        if (maxKolicina<=0) throw std::range_error("Ilegalna maksimalna kolicina");
       maxKol= maxKolicina;
    }
    void RegistrirajPadavine(int kol){
        if (kol<0 || kol>maxKol) throw std::range_error("Ilegalna kolicina padavina");
        padavine.push_back(kol);
    }
    int DajBrojRegistriranihPadavina() const{ return padavine.size();}
    void BrisiSve(){
        padavine=std::vector<int>{};
    }
    int DajMinimalnuKolicinuPadavina() const{
        if (padavine.size()==0) throw std::range_error("Nema registriranih padavina");
        return *std::min_element(padavine.begin(), padavine.end());
    }
    int DajMaksimalnuKolicinuPadavina() const{
        if (padavine.size()==0) throw std::range_error("Nema registriranih padavina");
        return *std::max_element(padavine.begin(), padavine.end());
    }
    int DajBrojDanaSaPadavinamaVecimOd(int kolicina) const{
        if (padavine.size()==0) throw std::range_error("Nema registriranih padavina");
        return std::count_if(padavine.begin(), padavine.end(), std::bind(std::greater<int>(), std::placeholders::_1, kolicina));
    }
    void Ispisi() const;
    
    int operator[](int ind){
        if (ind<=0 || ind>padavine.size()) throw std::range_error("Neispravan indeks");
        return padavine[ind-1];
    }
    Padavine& operator++();
    Padavine operator++(int);
    friend Padavine operator+(int y, const Padavine&x);
    friend Padavine operator+(const Padavine&x, int y);
    friend Padavine operator-(const Padavine &x, int y);
    friend Padavine operator-(int y, const Padavine&x);
    friend Padavine operator-(const Padavine&x, const Padavine &y);
    Padavine& operator+=(int y);
    Padavine& operator+=(const Padavine& x);
    Padavine& operator-=(const Padavine&y);
    Padavine& operator-=(int y);
     friend Padavine operator-(const Padavine& x);
     friend bool operator==(const Padavine &x, const Padavine &y);
     friend bool operator!=(const Padavine &x, const Padavine &y);
    
};
Padavine& Padavine::operator-=(const Padavine& y){
    if (padavine.size() != y.padavine.size()) 
        throw std::domain_error("Nesaglasni operandi");
    std::transform(padavine.begin(), padavine.end(), y.padavine.begin(), padavine.begin(), std::minus<int>());
    if (*std::min_element(padavine.begin(), padavine.end()) < 0) 
        throw std::domain_error("Nekorektan rezultat operacije");
    return *this;
}

bool operator==(const Padavine& x, const Padavine& y) {
    std::vector<int> p1 = x.padavine;
    std::vector<int> p2= y.padavine;
    std::sort(p1.begin(), p1.end());
    std::sort(p2.begin(), p2.end());
    return p1== p2;
}
bool operator!=(const Padavine&x, const Padavine&y){
    return !(x==y);
}
Padavine operator-(const Padavine&x){
    Padavine novi(x.maxKol);
    novi.padavine.resize(x.padavine.size());
    std::transform(x.padavine.begin(),x.padavine.end(),novi.padavine.begin(),std::bind(std::minus<int>(),x.maxKol,std::placeholders::_1));
    return novi;
}
Padavine& Padavine::operator-=(int y){
    *this=*this-y;
    return *this;
}
Padavine& Padavine::operator+=(int y){
    *this=*this+y;
    return *this;
}
Padavine operator+(const Padavine& x, int y) {
    Padavine novi(x.maxKol + y);
    novi.padavine.resize(x.padavine.size());
    std::transform(x.padavine.begin(), x.padavine.end(), novi.padavine.begin(), std::bind(std::plus<int>(), std::placeholders::_1, y));
    if (*std::min_element(novi.padavine.begin(), novi.padavine.end()) < 0) 
        throw std::domain_error("Nekorektan rezultat operacije");
    return novi;
}

Padavine operator+(int y, const Padavine& x) {
    return x + y;
}

Padavine operator-(const Padavine& x, int y) {
    Padavine novi(x.maxKol - y);
    novi.padavine.resize(x.padavine.size());
    std::transform(x.padavine.begin(), x.padavine.end(), novi.padavine.begin(), std::bind(std::minus<int>(), std::placeholders::_1, y));
    if (*std::min_element(novi.padavine.begin(), novi.padavine.end()) < 0) 
        throw std::domain_error("Nekorektan rezultat operacije");
    return novi;
}

Padavine operator-(int y, const Padavine& x) {
    Padavine novi(y);
    novi.padavine.resize(x.padavine.size());
    std::transform(x.padavine.begin(), x.padavine.end(), novi.padavine.begin(), std::bind(std::minus<int>(), y, std::placeholders::_1));
    if (*std::min_element(novi.padavine.begin(), novi.padavine.end()) < 0) 
        throw std::domain_error("Nekorektan rezultat operacije");
    return novi;
}

Padavine operator-(const Padavine& x, const Padavine& y) {
    if (x.padavine.size() != y.padavine.size()) 
        throw std::domain_error("Nesaglasni operandi");
    Padavine novi(x.maxKol);
    novi.padavine.resize(x.padavine.size());
    std::transform(x.padavine.begin(), x.padavine.end(), y.padavine.begin(), novi.padavine.begin(), std::minus<int>());
    if (*std::min_element(novi.padavine.begin(), novi.padavine.end()) < 0) 
        throw std::domain_error("Nesaglasni operandi");
    return novi;
}

Padavine& Padavine::operator++(){
    maxKol++;
    std::transform(padavine.begin(), padavine.end(),padavine.begin(),std::bind(std::plus<int>(),std::placeholders::_1, 1));
    return *this;
}
Padavine Padavine::operator++(int){
Padavine temp(*this);
++(*this);
return temp;
}
void Padavine::Ispisi() const{
    std::vector<int> copy=padavine;
    std::sort(copy.begin(), copy.end(), std::greater<int>());
    for (auto p:copy) std::cout<<p<<std::endl;
}

int main ()
{
    Padavine p(100);
    p.RegistrirajPadavine(20);
    p.RegistrirajPadavine(30);
    p.RegistrirajPadavine(40);
    p.RegistrirajPadavine(50);
    std::cout << "registriranje " << p.DajBrojRegistriranihPadavina() << std::endl;
    std::cout << "min: " << p.DajMinimalnuKolicinuPadavina() << std::endl;
    std::cout << "max: " << p.DajMaksimalnuKolicinuPadavina() << std::endl;
    std::cout << "br dana sa : " << p.DajBrojDanaSaPadavinamaVecimOd(25) << std::endl;
    std::cout << "pad. 3. dan: " << p[3] << std::endl;
    ++p;
    std::cout << "p++" << p[3] << std::endl;
    p = p + 10;
    std::cout  << p[3] << std::endl;
    p = p - 10;
    std::cout  << p[3] << std::endl;
    p += 10;
    std::cout <<"+=" << p[3] << std::endl;
    p -= 10;
    std::cout  << p[3] << std::endl;
    Padavine p2(100);
    p2.RegistrirajPadavine(20);
    p2.RegistrirajPadavine(30);
    p2.RegistrirajPadavine(40);
    p2.RegistrirajPadavine(60); 
    std::cout << (p == p2) << std::endl;
    std::cout <<  (p != p2 ) << std::endl;
    p = -p;
    std::cout  << p[3] << std::endl;
    p2.RegistrirajPadavine(10); 
    p -= p2;
    std::cout << p[3] << std::endl;
    p.Ispisi();
	return 0;
}
