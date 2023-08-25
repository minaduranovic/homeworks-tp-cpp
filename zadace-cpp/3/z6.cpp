//TP 2022/2023: Zadaća 3, Zadatak 6
#include <iostream>
#include <cmath>
#include<list>
#include<memory>
struct Cvor{
    int redni_broj;
    std::shared_ptr<Cvor> sljedeci;
};
int Poglavica (int N, int M, bool ispis=false){
std::shared_ptr<Cvor> pocetak=nullptr;
std::shared_ptr<Cvor> prethodni=nullptr;
if (N<=0 || M<=0) return 0;
for (int i=1; i<=N; i++){
   std::shared_ptr<Cvor> novi=std::make_shared<Cvor>();
   novi->redni_broj=i;
    if (pocetak==nullptr ) pocetak=novi;////
    else prethodni->sljedeci=novi;

    prethodni=novi;
}
prethodni->sljedeci=pocetak;

std::shared_ptr<Cvor> trenutni=pocetak;

while (N>1){
    for (int i=0; i<M-1; i++){
        prethodni=trenutni;
        trenutni=trenutni->sljedeci;

    }
    prethodni->sljedeci=trenutni->sljedeci;
   std::shared_ptr<Cvor> temp=trenutni;
    trenutni=trenutni->sljedeci;
        if (ispis) {
        std::cout<<temp->redni_broj;
        // if (N>2){
            std::cout<<", ";
        // }
    }
    N--;
}
int poglavica=trenutni-> redni_broj;

if (trenutni == trenutni->sljedeci) {
    trenutni->sljedeci = nullptr;
    trenutni = nullptr;
}
return poglavica;
  
}
int SigurnoMjesto(int M, int N1, int N2){
    int sigurno=0;
    int min=N2+1;
    if (M<=0 || N1<=0 || N2<=0) return 0;
    for (int i=N1; i<=N2; i++){
       bool flag=true;
       for (int j=N1; j<=N2; j++){
           int poglavica=Poglavica(j, M);
           if (poglavica==i){
               flag=false;
               break;
           }
       }
       if (flag){
           sigurno=i;
           break;
       }
    }
    return sigurno;
}
int main ()
{
int n, M, N1,N2;
std::cout<<"Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
std::cin>>n;
std::cout<<"Unesite korak razbrajanja: ";
std::cin>>M;
std::cout<<"Unesite raspon za odabir (N1 i N2): ";
std::cin>>N1>>N2;
int poglavica=Poglavica(n, M);
std::cout<<"Redni broj osobe koja postaje poglavica: "<<poglavica<<std::endl;

int sigurno=SigurnoMjesto(M, N1, N2);
if (sigurno !=0) std::cout<<"Mbebe Mgogo, stani na sigurno mjesto "<<sigurno<<" da ne bi bio poglavica!";
else std::cout<<"Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
	return 0;
}