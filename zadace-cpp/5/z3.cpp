//TP 2022/2023: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include<vector>
#include <algorithm>
#include <functional>
#include <fstream>

class ApstraktnoVozilo{
protected:
int tezina;
public:
virtual ~ApstraktnoVozilo()=default;
ApstraktnoVozilo(int tez): tezina(tez){}
int DajTezinu()const{return tezina;}
virtual int DajUkupnuTezinu() const=0;
virtual ApstraktnoVozilo*DajKopiju()const =0;
virtual void IspisiPodatke() const=0;
};

class Automobil: public ApstraktnoVozilo{
    std::vector<int> putnici;
    public:
    virtual ~Automobil()=default;
    Automobil(int tezina,std::vector<int> tezPutnika): ApstraktnoVozilo(tezina), putnici(tezPutnika){}
    int DajUkupnuTezinu()const override{
        int ukupno=tezina;
        for (auto tez: putnici) ukupno+=tez;
        return ukupno;
    }
    void IspisiPodatke() const override;
    Automobil*DajKopiju() const override{return new Automobil(*this);}
};
void Automobil::IspisiPodatke() const{
    std::cout<<"Vrsta vozila: Automobil\n"<<"Vlastita tezina: "<<tezina<<" kg\n";
    std::cout<<"Tezine putnika: ";
    for (int i=0; i<putnici.size(); i++){
        std::cout<<putnici[i]<<" kg";
        if (i!=putnici.size()-1) std::cout<<", ";
    }
    std::cout<<"\nUkupna tezina: "<< DajUkupnuTezinu()<<" kg\n";

}
class Kamion: public ApstraktnoVozilo{
    int teret;
    public: 
    virtual ~Kamion()=default;
    Kamion(int tez, int tezinaTereta):ApstraktnoVozilo(tez), teret(tezinaTereta){}
int DajUkupnuTezinu() const override{
    return tezina+teret;
}
    void IspisiPodatke() const override;
    Kamion* DajKopiju() const override{ return new Kamion(*this);}
};
void Kamion::IspisiPodatke()const{
     std::cout << "Vrsta vozila: Kamion\nVlastita tezina: " << tezina << " kg\n";
    std::cout << "Tezina tereta: " << teret << " kg\nUkupna tezina: " << DajUkupnuTezinu() << " kg\n";
}
class Autobus: public ApstraktnoVozilo{
    int brPutnika;
    int avg;
    public:
    virtual ~Autobus()=default;
   Autobus(int tezina, int brojPutnika, int prosjecna): 
        ApstraktnoVozilo(tezina), brPutnika(brojPutnika), avg(prosjecna){}
    int DajUkupnuTezinu() const override {
        return tezina + brPutnika * avg;
    }
    void IspisiPodatke() const override;
    Autobus* DajKopiju() const override { return new Autobus(*this); }
};
void Autobus::IspisiPodatke() const {
    std::cout << "Vrsta vozila: Autobus\nVlastita tezina: " << tezina << " kg\n";
    std::cout << "Broj putnika: " << brPutnika << "\nProsjecna tezina putnika: " << avg << " kg\n";
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg\n";
}

class Vozilo {
    ApstraktnoVozilo* vozilo;
public:
   Vozilo(const ApstraktnoVozilo& vozilo): vozilo(vozilo.DajKopiju()) {}
    Vozilo(const Vozilo& v) : vozilo(v.vozilo->DajKopiju()) {}
    Vozilo& operator=(const Vozilo& v) {
        if (&v != this) {
            delete vozilo;
            vozilo = v.vozilo->DajKopiju();
        }
        return *this;
    }
    int DajUkupnuTezinu() const{
        return vozilo->DajUkupnuTezinu();
    }
    void IspisiPodatke() const{
        return vozilo->IspisiPodatke();
    }
    ~Vozilo() { delete vozilo; }
};

int main() {
    std::vector<Vozilo> vozila;
    std::ifstream ulazni("VOZILA.TXT");
    if (!ulazni) {
        std::cout << "Greska pri otvaranju datoteke";
        return 1;
    }
    char vrsta;
    while (ulazni >> vrsta) {
        int tezina;
        ulazni >> tezina;
        if (vrsta == 'A') {
            int brPutnika;
            ulazni >> brPutnika;
            std::vector<int> putnici(brPutnika);
            for (int i = 0; i < brPutnika; i++) {
                ulazni >> putnici[i];
            }
            vozila.push_back(Automobil(tezina, putnici));
        }
        else if (vrsta == 'K') {
            int teret;
            ulazni >> teret;
            vozila.push_back( Kamion(tezina, teret));
        }
        else if (vrsta == 'B') {
            int brPutnika, avg;
            ulazni >> brPutnika >> avg;
            vozila.push_back( Autobus(tezina, brPutnika, avg));
        }
        else {
            std::cout << "Izuzetak: NEPOSTOJECE VOZILO!";
            return 1;
        }
    }
    std::sort(vozila.begin(), vozila.end(), [](const Vozilo& a, const Vozilo& b) {
        return a.DajUkupnuTezinu() < b.DajUkupnuTezinu();
    });

    for (const auto& x: vozila){
        std::cout << x.DajUkupnuTezinu() << std::endl;
    }
    return 0;
}
