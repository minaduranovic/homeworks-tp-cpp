//TP 2022/2023: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include<iomanip>
#include <algorithm>
#include <string>
template<typename t>
bool grbava(std::vector<std::vector<t>> mat){
   int m=mat.at(0).size();
   for (int i=0; i<mat.size(); i++){
       if(mat.at(i).size()!=m) return false;
   }
  return true;
}
template<typename t1, typename t2, typename tipF, typename tipG>
auto GeneraliziraniMatricniProizvod( std::vector<std::vector<t1>> a,  std::vector<std::vector<t2>> b , tipF f, tipG g ){
    if ( a.at(0).size()!=b.size()){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
     if ( (a.size()==0 || a.at(0).size()==0 || b.size()==0 || b.at(0).size()==0) && (a.at(0).size()==b.size())) 
        return std::vector<std::vector<typename std::remove_reference<decltype(f(g(a.at(0).at(0), b.at(0).at(0)), g(a.at(0).at(0), b.at(0).at(0))))>::type>>(b.size(),std::vector<typename std::remove_reference<decltype(f(g(a.at(0).at(0), b.at(0).at(0)), g(a.at(0).at(0), b.at(0).at(0))))>::type>(a.at(0).size()));

    if(!grbava(a) || !grbava(b)) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    using tipR= typename std::remove_reference<decltype(f(g(a.at(0).at(0), b.at(0).at(0)), g(a.at(0).at(0), b.at(0).at(0))))>::type;
    
    std::vector<std::vector<tipR>> c(a.size(), std::vector<tipR> (b.at(0).size()));
    try{
        for (int i=0; i<a.size(); i++){
            for (int j=0; j<b.at(0).size(); j++){
                c.at(i).at(j)=g(a.at(i).at(0), b.at(0).at(j));
                for (int k=1; k<a.at(0).size(); k++){
                    c.at(i).at(j)=f(c.at(i).at(j), g(a.at(i).at(k), b.at(k).at(j)));
                }
            }
        }
    }
    catch(...){
        throw std::runtime_error("Neocekivani problemi pri racunanju");
    }
    return c;
}
template< typename t>
const t&veci(const t&a, const t&b){
    return (a<b)?b:a;
}

int main ()
{
    int m,n ,p;
    std::cout<<"Unesite broj redova prve matrice: ";
    std::cin>>m;
    std::cout<<"Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
    std::cin>>n;
    std::cout<<"Unesite broj kolona druge matrice: ";
    std::cin>>p;
    std::vector<std::vector<std::string>> a(m, std::vector<std::string> (n)),b(n, std::vector<std::string> (p));
    std::cout<<"Unesite elemente prve matrice: ";
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            std::cin>>a.at(i).at(j);
        }
    }
     std::cout<<"Unesite elemente druge matrice: ";
    for (int i=0; i<n; i++){
        for (int j=0; j<p; j++){
            std::cin>>b.at(i).at(j);
        }
    }
    auto f=[](const std::string &s1, const std::string &s2){return s1 + "+" +s2;};
    auto g=[](const std::string &s1, const std::string &s2){return s1+ "*" +s2;};
std::cout<<"Matricni proizvod:\n";
    try{
        auto c=GeneraliziraniMatricniProizvod(a, b, f, g);
            int maxel=0;
            for (const auto &red: c){
                for (const auto &elem: red ){
                    maxel=veci(maxel, static_cast<int>(elem.length()));
                }
            }
            for (const auto &red: c){
                for (const auto &elem: red ){
                    std::cout<<std::left<<std::setw(maxel+1)<<elem;
                }
                std::cout<<std::endl;
            }
        }
    catch(std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
	return 0;
}
