//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <complex>

constexpr double eps=1e-10;
class Sinusoida{
double amplituda;
double frekvencija;
double faza;

void normal(){
    if (amplituda<0){
        amplituda=-amplituda;
        faza+=(4*atan(1));
    }
    while (faza>4*atan(1)){
        faza-=(2*4*atan(1));
    }
    while (faza<-4*atan(1)){
        faza+=(2*4*atan(1));
    }
    if (frekvencija<0){
        frekvencija=-frekvencija;
        faza=-faza;
        faza+=(4*atan(1));
         while (faza>4*atan(1)){
        faza-=(2*4*atan(1));
    }
    while (faza<-4*atan(1)){
        faza+=(2*4*atan(1));
    }
    }
}

public:
Sinusoida(double a, double f, double fi):amplituda(a), frekvencija(f), faza(fi){
    normal();
}
double DajAmplitudu()const {return amplituda;}
double DajFrekvenciju()const {return frekvencija;}
double DajFazu()const {return faza;}

std::tuple<double, double, double> DajParametre() const{return  std::make_tuple(amplituda,frekvencija,faza);}
Sinusoida& PostaviAmplitudu(double a){
    amplituda=a;
    normal();
    return *this;
}
Sinusoida& PostaviFrekvenciju(double f){
    frekvencija=f;
    normal();
    return *this;
}
Sinusoida& PostaviFazu(double fi){
    faza=fi;
    normal();
    return *this;
}

Sinusoida& PostaviParametre(std::tuple<double,double,double> parametri);

friend Sinusoida operator+(const Sinusoida& v1, const Sinusoida &v2);
friend Sinusoida operator-(const Sinusoida &v1, const Sinusoida &v2);
friend Sinusoida operator*(double broj,const Sinusoida &v1);
friend Sinusoida operator*(const Sinusoida &v1, double broj);
friend Sinusoida operator/(const Sinusoida&v1, double broj);

Sinusoida operator-();
Sinusoida& operator+=(const Sinusoida&s);
Sinusoida& operator-=(const Sinusoida&s);
Sinusoida& operator*=(double broj);
Sinusoida& operator/=(double broj);
double& operator[](const std::string &s);
double operator[](const std::string &s) const;
double operator ()(double t)const;

};

Sinusoida& Sinusoida::PostaviParametre(std::tuple<double, double, double> parametri){
    double a,f,fi;
    std::tie(a,f,fi)=parametri;
    amplituda=a; frekvencija=f; faza=fi;
    normal();
    return *this;
}
Sinusoida operator+(const Sinusoida&v1, const Sinusoida&v2){
     if (std::abs(v1.frekvencija - v2.frekvencija )> 1e-9) {
        throw std::domain_error("Razlicite frekvencije");
    }
    std::complex<double> c1(v1.amplituda * cos(v1.faza), v1.amplituda * sin(v1.faza));
    std::complex<double> c2(v2.amplituda * cos(v2.faza), v2.amplituda * sin(v2.faza));
    std::complex<double> novi = c1 + c2;
    return Sinusoida(std::abs(novi), v1.frekvencija, std::arg(novi));
}
Sinusoida operator-(const Sinusoida&v1, const Sinusoida&v2){
 if(v1.frekvencija != v2.frekvencija)
        throw std::domain_error("Razlicite frekvencije");

    std::complex<double> c1(v1.amplituda * cos(v1.faza), v1.amplituda * sin(v1.faza));
    std::complex<double> c2(v2.amplituda * cos(v2.faza), v2.amplituda * sin(v2.faza));
    auto novi = c1 - c2;
    return Sinusoida(std::abs(novi), v1.frekvencija, atan2(novi.imag(),novi.real()));
}
Sinusoida operator*( double broj, const Sinusoida& v1){
    return Sinusoida(v1.amplituda*broj,v1.frekvencija,v1.faza);
}
Sinusoida operator*(const Sinusoida&v1, double broj){
    return broj*v1;
}
Sinusoida operator/(const Sinusoida&v1, double broj){
    return (1.0/broj)* v1;
}
double& Sinusoida::operator[](const std::string &s) {
    if (s!="A"& s!="omega" &s!="fi" &s!="phi"&s!="w") throw std::domain_error("Neispravan naziv parametra");
    if (s=="A") return amplituda;
    else if (s=="omega"|| s=="w") return  frekvencija;
    else  return faza;
}
double Sinusoida::operator()(double t) const{
    return amplituda*sin(frekvencija*t+faza);
}
Sinusoida& Sinusoida::operator+=(const Sinusoida &s){
 *this=*this+s;
 return *this;
}
Sinusoida& Sinusoida::operator-=(const Sinusoida&s){
    *this=*this-s;
    return *this;
}
Sinusoida& Sinusoida::operator*=(double broj) {
    *this = *this * broj;
    return *this;
}

Sinusoida& Sinusoida::operator/=(double broj) {
    *this = *this / broj;
    return *this;
}
Sinusoida Sinusoida::operator-() {
    return Sinusoida(-amplituda, frekvencija, faza);
}

double Sinusoida::operator[](const std::string &s) const {
    if (s != "A" && s != "omega" && s != "fi" && s != "phi" && s != "w") throw std::domain_error("Neispravan naziv parametra");
    if (s == "A") return amplituda;
    else if (s == "omega" || s == "w") return frekvencija;
    else return faza;
}
int main ()
{
    Sinusoida s1(1, 1, 0);
    Sinusoida s2(1, 1, 3.14 / 2);
    auto params = s1.DajParametre();
    std::cout << "Sinusoida s1: A = " << std::get<0>(params) << ", omega = " << std::get<1>(params) << ", phi = " << std::get<2>(params) << "\n";

    params = s2.DajParametre();
    std::cout << "Sinusoida s2: A = " << std::get<0>(params) << ", omega = " << std::get<1>(params) << ", phi = " << std::get<2>(params) << "\n";

    try {
        Sinusoida s3 = s1 + s2;
        params = s3.DajParametre();
        std::cout << "Sinusoida s3 = s1 + s2: A = " << std::get<0>(params) << ", omega = " << std::get<1>(params) << ", phi = " << std::get<2>(params) << "\n";
    } catch (std::domain_error &e) {
        std::cout << e.what() << "\n";
    }
    try {
        std::cout << "s1[\"A\"] = " << s1["A"] << "\n";
    } catch (std::domain_error &e) {
        std::cout << e.what() << "\n";
    }
    std::cout << "s1(0) = " << s1(0) << "\n";

	return 0;
}
