//TP 2022/2023: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <new>
#include <stdexcept>
#include <vector>
#include <deque>
#include <array>
#include<list>

template <typename tip1, typename tip2>
auto KreirajTablicuSabiranja(tip1 poc1, tip1 kraj, tip2 poc2){
    using povrTip=decltype(*poc1+*poc2);
    int n=0;
    auto temp=poc1;
    while (temp!=kraj) {
        temp++;
        n++;
    }
    povrTip **mat=nullptr;
    try{
        mat=new povrTip*[n];
        for (int i=0; i<n; i++){
            mat[i]=nullptr;
        }
        mat[0]=new povrTip[n*(n+1)/2];
        for (int i=1; i<n; i++){
            mat[i]=mat[i-1]+i;
        }
         tip1 pok1=poc1;
         try{
        for (int i=0; i<n; i++){
            tip2 pok2=poc2;
            for (int j=0; j<=i; j++){
                mat[i][j]=*pok1+*pok2;
                if (mat[i][j]!=*pok2+*pok1){
                    delete[] mat[0];
                    delete[] mat;
                    throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
                }
                pok2++;
            }
            pok1++;
        }
         }catch(std::bad_alloc){
             delete[] mat[0];
             delete[] mat;
             throw std::range_error("Nema dovoljno memorije!");
         }
    }catch(std::bad_alloc &e){
        delete[] mat[0];
        delete[] mat;
        throw std::range_error("Nema dovoljno memorije!");
    }
    return mat;
}

int main ()
{
    int n;
std::cout<<"Duzina sekvenci: ";
std::cin>>n;
std::cout<<"Elementi prve sekvence: ";
std::vector<double> v(n);
std::deque<double> d(n);
for (int i=0; i<n; i++){
    std::cin>>v.at(i);
}
std::cout<<"Elementi druge sekvence: ";
for (int i=0; i<n; i++){
    std::cin>>d.at(i);
}
decltype(KreirajTablicuSabiranja(v.begin(), v.end(), d.begin())) matrica=nullptr;
try{
     matrica=KreirajTablicuSabiranja(v.begin(), v.end(), d.begin());
std::cout<<"Tablica sabiranja: ";

for (int i=0; i<n; i++){
    for(int j=0; j<=i; j++){
        std::cout<<matrica[i][j]<<" ";
    }
    std::cout<<std::endl;
}
}catch(std::bad_alloc& e){
    std::cout<<"Izuzetak: "<<e.what();
}
delete[] matrica[0];
delete[] matrica;
	return 0;
}
