//TP 2022/2023: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include<list>

int Poglavica (int N, int M, bool ispis=false){
    std::list<int> pleme;

    for (int i=1; i<=N; i++){
        pleme.push_back(i);
    }
if (M<=0) return 0;//
auto iter1 =pleme.begin();
auto iter2=pleme.end();

while(pleme.size()>1){
    for (int i=0; i<M-1; i++){
        iter1++;
        if (iter1==iter2){
            iter1=pleme.begin();
        }
    }
    if (ispis) {
        std::cout<<*iter1;
        // if (pleme.size()>2){
            std::cout<<", ";
        // }
    }
    iter1=pleme.erase(iter1);
    if(iter1==iter2){
        iter1=pleme.begin();
    }
}
return *pleme.begin();
}
int SigurnoMjesto(int M, int N1, int N2){
    int sigurno=0;
    int min=N2+1;
    if (M<=0) return 0;//
    if (N1<=0 || N2<=0) return 0;//
    for (int i=N1; i<=N2; i++){
        bool flag=true;
    for (int j=N1; j<=N2; j++){
        int poglavica=Poglavica(j,  M);
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
