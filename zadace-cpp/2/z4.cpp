//TP 2022/2023: Zadaća 2, Zadatak 4
#include <exception>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


template<typename tip1>
bool Kriterij(const std::vector<tip1> &v1, const std::vector<tip1> &v2){
if (v1.size()==0 || v2.size()==0) return false;

tip1 pr1=v1.at(0), pr2=v2.at(0);

for(int i=1; i<v1.size(); i++) pr1=pr1*v1.at(i);
for(int i=1; i<v2.size(); i++) pr2=pr2*v2.at(i);
if (!(pr1==pr2)) return pr1<=pr2;
for (int i=0; i<v1.size(); i++){
    if (!(v1.at(i)==v2.at(i))){
        return v1.at(i)<=v2.at(i);
    }
}
return false;
}
template<typename tip2>
void SortirajPoProizvoduRedova(std::vector<std::vector<tip2>> &mat){
std::sort(mat.begin(), mat.end(), Kriterij<tip2>);
}
int main ()
{
std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
std::vector<std::vector<int>> mat;
std::string s;
while (true){
    std::cin>>s;
    if (s=="*" || s.length()==0) break;
    std::vector<int> red;
      int   br;
      try{
      br=std::stoi(s);
        red.push_back(br);
      }catch(std::exception &e){
          break;
      }
      while (std::cin.peek()!='\n'){
          std::cin>>s;
          try{
              br=std::stoi(s);
              red.push_back(br);
          }catch(std::exception &e){
              break;
          }   
      }
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      mat.push_back(red);
}
SortirajPoProizvoduRedova(mat);
std::vector<int> sekv;
std::cout<<"\n\nMatrica nakon sortiranja: "<<std::endl;
for (int i=0; i<mat.size(); i++){
    for (int j=0; j<mat.at(i).size(); j++){
        std::cout<<mat.at(i).at(j)<<" ";
    }
    std::cout<<std::endl;
}
std::cout<<"\nUnesite elemente sekvence koja se trazi (* za kraj reda):";
int broj;
while(std::cin>>broj) sekv.push_back(broj);
auto iter=  std::lower_bound(mat.begin(), mat.end(),sekv,Kriterij<int>);
if (*iter==sekv && iter!=mat.end()){
    int ind=1;
    for (const auto&red:mat){
        if (red==sekv) break;
        ind++;
    }
    std::cout<<"\nTrazena sekvenca se nalazi u "<< ind<<". redu (nakon sortiranja)";
}else{
    std::cout<<"\nTrazena sekvenca se ne nalazi u matrici";
}
	return 0;
}
