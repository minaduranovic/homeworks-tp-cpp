//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <map>
#include <tuple>
#include<set>
#include <algorithm>
#include<cctype>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int ,int>>>Indeks;

bool nijeSlovo(char c){
    if ((c>=' ' && c<='/') || (c>=':' && c<='@')) return true;
    return false;
}
Indeks KreirajIndeksPojmova(const Knjiga& knjiga){
Indeks rez;

for (auto& poglavlje :knjiga){
    const std::string &pogl=poglavlje.first;
    const std::vector<std::string>& vektor=poglavlje.second;
    for (int i=0; i<vektor.size(); i++){
        const std::string &str=vektor[i];
        int poz=0;
        while (poz!=str.size()){
            int next=poz;
            while (next!= str.size() && !nijeSlovo(str[next])){
                next++;
            }
            if (next>poz){
                 std::string rijec=str.substr(poz,next-poz);
                std::transform(rijec.begin(), rijec.end(), rijec.begin(), tolower);
                std::set<std::tuple<std::string, int, int>> &skup=rez[rijec];
                skup.insert(std::make_tuple(pogl, i+1,poz));
                poz=next;
            }
            while(poz<str.size() && nijeSlovo(str[poz])){
                poz++;
            }

        }
    }
}
return rez;
}
std::set<std::tuple<std::string, int,int>> PretraziIndeksPojmova(const std::string&rijec, const Indeks &indeks){
    std::string nova=rijec;
    std::transform(nova.begin(), nova.end(), nova.begin(),tolower);
    auto it=indeks.find(nova);
    if (it!= indeks.end()) return it->second;
    else throw std::logic_error("Pojam nije nadjen");
}
void IspisiIndeksPojmova(const std::map<std::string, std::set<std::tuple<std::string,int,int>>> &indeks){
    for (auto p1=indeks.begin(); p1!=indeks.end(); p1++){
        std::cout<<p1->first<<": ";
        for (auto p2=p1->second.begin(); p2!=p1->second.end(); p2++){
           

            if (p2==std::prev(p1->second.end(),1) )std::cout<<std::get<0>(*p2)<<"/"<<std::get<1>(*p2)<<"/"<<std::get<2>(*p2);
            else std::cout<<std::get<0>(*p2)<<"/"<<std::get<1>(*p2)<<"/"<<std::get<2>(*p2)<<", ";
            
        }
        std::cout<<std::endl;
    }
}

int main ()
{
Knjiga knjiga;
std::string poglavlje,sadrzaj;
Indeks indeks;


while(true){
    std::cout<<"\nUnesite naziv poglavlja:";
    std::getline(std::cin, poglavlje);
    if (poglavlje==".") break;

    std::vector<std::string>stranice;
    int br=1;
    while(true){
        std::cout<<"\nUnesite sadrzaj stranice "<< br<<":";
        std::getline(std::cin, sadrzaj);
        if (sadrzaj==".") break;
        stranice.push_back(sadrzaj);
        br++;
    }
    knjiga[poglavlje]=stranice;
}
indeks=KreirajIndeksPojmova(knjiga);
std::cout<<"\nKreirani indeks pojmova:"<<std::endl;
IspisiIndeksPojmova(indeks);
while(true){
    std::string rijec;
    std::cout<<"Unesite rijec: ";
    std::getline(std::cin, rijec);
    if (rijec==".") break;
    try{
        std::set<std::tuple<std::string,int ,int>> rezultat=PretraziIndeksPojmova(rijec, indeks);
        
            for (const auto &trojka: rezultat){
                std::cout<<std::get<0>(trojka)<<"/"<<std::get<1>(trojka)<<"/"<<std::get<2>(trojka)<<" ";
            }
        
    }catch(std::logic_error ){
        std::cout<<"Unesena rijec nije nadjena!";
    }
    std::cout<<"\n";
}

	return 0;
}
