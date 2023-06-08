//TP 2022/2023: Zadaća 2, Zadatak 2        
#include <cstdint>
#include <iostream>
#include <cmath>
#include<limits>
bool prost(int n){
    if (n<=0 || n==1) return false;

    for (int i=2; i<=sqrt(n); i++){
        if(n%i==0) return false;
    }
     return true;
}

void RastavaBroja(int n, int &p, int &q){
bool neg=false;
int x=2;
p=1,q=1;
if (n<0){
n=-n;
neg=true;
}
if (n==0){
    p=0;
    q=1;
   
} else if (prost(n)){
p=n;
q=1;
}else{  
    
    while(-x*x<=n){
        int count=0;
        while(n%x==0){
            count++;
            n/=x;
        }
        if (count>0){
            if (count%2==1){
                p*=x;
            }
            q*=std::pow(x, count/2);
        }
        x++;
    }
    if(n<0) p=n;
if (n>1){
        p*=n;
        q*=std::pow(x,0);
    }
}
if (neg) p=-p;
}
int main ()
{
int broj;
std::cout<<"Unesi broj: \n";
std::cin>>broj;
int p,q;

RastavaBroja(broj, p, q);
std::cout<<broj<<" = "<<p<<"*"<<q<<"^2";
	return 0;
}
