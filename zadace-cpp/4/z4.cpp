//TP 2022/2023: Zadaća 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <iterator>
#include <stdexcept>
#include <string>
#include <map>
#include <memory>
//klasa korisnik
class Korisnik{
    int cl_br;
    std::string ime_prezime;
    std::string adresa;
    std::string br_tel;
    
    public:
    Korisnik(int cl_broj, std::string ime_pr, std::string adr, std::string br_tl):cl_br(cl_broj), ime_prezime(ime_pr), adresa(adr), br_tel(br_tl) {}
    int DajClanskiBroj()const {return cl_br;}
    std::string DajImeIPrezime()const {return ime_prezime;}
    std::string DajAdresu()const {return adresa;}
    std::string DajTelefon() const{return br_tel;}
    void Ispisi() const;
};
void Korisnik::Ispisi() const{
        std::cout<<"Clanski broj: "<< cl_br<<std::endl<<"Ime i prezime: "<< ime_prezime<<std::endl<<"Adresa: "<<adresa<<std::endl<< "Telefon: "<<br_tel<<std::endl;
    }
//klasa film
class Film{
int evid_br;
bool na_traci;
std::string naziv;
std::string zanr;
int produkcija;
Korisnik* zaduzen;

public:
Film(int evidencijski, bool da_li_je, std::string ime, std::string zanr_filma, int izdavanje): evid_br(evidencijski), na_traci(da_li_je),naziv(ime) ,zanr(zanr_filma), produkcija(izdavanje){zaduzen=nullptr;}
int DajEvidencijskiBroj() const{ return evid_br;}
std::string DajNaziv() const {return naziv;}
std::string DajZanr()const{ return zanr;}
int DajGodinuProdukcije() const {return produkcija;}
bool DaLiJeDVD() const{ return na_traci;}
void ZaduziFilm( Korisnik& korisnik){ zaduzen=&korisnik;}
void RazduziFilm(){delete zaduzen; zaduzen=nullptr;}
bool DaLiJeZaduzen() const{if (zaduzen==nullptr) return false; return true;}
Korisnik& DajKodKogaJe() {if (zaduzen==nullptr) throw  std::domain_error("Film nije zaduzen");return *zaduzen;}
Korisnik* DajPokKodKogaJe() const{ return zaduzen;}
void Ispisi()const;

};
void Film::Ispisi() const{
    std::cout<<"Evidencijski broj: "<<evid_br<<std::endl<<"Medij: ";
    if (na_traci) std::cout<<"DVD\n";
    else std::cout<<"Video traka\n";
    std::cout<<"Naziv filma: "<<naziv<<std::endl;
    std::cout<<"Zanr: "<<zanr<<std::endl;
    std::cout<<"Godina produkcije: "<<produkcija<<std::endl;
}

//klasa Videoteka
class Videoteka{
std::map<int ,std::shared_ptr<Korisnik>> mapa_korisnika;
std::map<int, std::shared_ptr<Film>> mapa_filmova;

public:
Videoteka(){}
Videoteka (const Videoteka& objekat);
Videoteka& operator=(const Videoteka& objekat);
Videoteka (Videoteka && objekat);
Videoteka& operator=(Videoteka && objekat);
void RegistrirajNovogKorisnika (int cl_broj,std::string ime_prezime, std::string adr, std::string broj_tel);
void RegistrirajNoviFilm(int eviden,bool ne_na_traci,std::string naziv_filma, std::string zanr_filma, int izadanje);
Korisnik& NadjiKorisnika(int clanski){if (mapa_korisnika.count(clanski)==0) throw std::logic_error ("Korisnik nije nadjen"); return *mapa_korisnika[clanski]; }
Film& NadjiFilm(int eviden){ if (mapa_filmova.count(eviden)==0) throw std::logic_error("Film nije nadjen"); return *mapa_filmova[eviden];}
void IzlistajKorisnike() const;
void IzlistajFilmove() const;
void ZaduziFilm(int eviden, int clanski);
void RazduziFilm(int eviden);
void PrikaziZaduzenja  (int cl_broj)const;

};

Videoteka::Videoteka(const Videoteka& objekat){
    for (const auto& par: objekat.mapa_korisnika){
        mapa_korisnika[par.first]=std::make_shared<Korisnik>(*par.second);
    }
    for (const auto& par: objekat.mapa_filmova){
        mapa_filmova[par.first]=std::make_shared<Film>(*par.second);
    }
}
Videoteka& Videoteka:: operator=(const Videoteka& objekat){
    if (&objekat!=this){
        Videoteka temp(objekat);
   //moguce     
        mapa_korisnika.swap(temp.mapa_korisnika);
        mapa_filmova.swap(temp.mapa_filmova);
    }
    return *this;
}
Videoteka::Videoteka(Videoteka && objekat): mapa_korisnika(std::move(objekat. mapa_korisnika)), mapa_filmova(std::move(objekat.mapa_filmova)){}
Videoteka& Videoteka::operator=(Videoteka && objekat){
    if (&objekat!=this){
        mapa_korisnika=std::move(objekat.mapa_korisnika);
        mapa_filmova=std::move(objekat.mapa_filmova);
    }
    return *this;
}
void Videoteka::RegistrirajNovogKorisnika(int cl_broj,std::string ime_prezime, std::string adr, std::string broj_tel ){
    if (mapa_korisnika.count(cl_broj)>0){
        throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
    }
    mapa_korisnika[cl_broj]=std::make_shared<Korisnik>(cl_broj,ime_prezime,adr, broj_tel);
}

void Videoteka::RegistrirajNoviFilm(int eviden, bool ne_na_traci, std::string naziv_filma, std::string zanr_filma, int izadanje){
    if (mapa_filmova.count(eviden)>0){
        throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
    }
    mapa_filmova[eviden]=std::make_shared<Film>(eviden, ne_na_traci, naziv_filma,zanr_filma,izadanje);
}
void Videoteka::IzlistajKorisnike() const{
    for (const auto &par: mapa_korisnika){
        par.second->Ispisi();
        std::cout<<std::endl;
    }
}
void Videoteka::IzlistajFilmove() const{
    for (const auto &par: mapa_filmova){
        par.second->Ispisi();
        if (par.second->DaLiJeZaduzen()){
            std::cout<<"Zaduzen kod korisnika: "<<par.second->DajKodKogaJe().DajImeIPrezime()<<" ("<<par.second->DajKodKogaJe().DajClanskiBroj()<<")\n";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void Videoteka::ZaduziFilm(int eviden, int clanski){
  if (mapa_filmova.count(eviden) == 0) {
            throw std::logic_error("Film nije nadjen");
        }
        if (mapa_korisnika.count(clanski == 0)) {
            throw std::logic_error("Korisnik nije nadjen");
        }
        Film& film = *mapa_filmova[eviden];
        if (film.DaLiJeZaduzen()) {
            throw std::logic_error("Film vec zaduzen");
        }

film.ZaduziFilm(NadjiKorisnika(clanski));
//zaduzivanje
}
void Videoteka::RazduziFilm(int eviden){
     if (mapa_filmova.count(eviden) == 0) {
        throw std::logic_error("Film nije nadjen");
    }

    Film& film = *mapa_filmova[eviden];
    if (!film.DaLiJeZaduzen()) {
        throw std::logic_error("Film nije zaduzen");
    }

    film.RazduziFilm();
}
void Videoteka::PrikaziZaduzenja (int cl_broj) const{
    auto it = mapa_korisnika.find(cl_broj);
    if (it == mapa_korisnika.end()) {
        throw std::logic_error("Korisnik nije nadjen");
    }

    const Korisnik& korisnik = *(it->second);
    bool ima_zaduzenja = false;

    for (const auto& pair : mapa_filmova) {
        Film& film = *(pair.second);
        if (film.DaLiJeZaduzen() && film.DajKodKogaJe().DajClanskiBroj() == cl_broj) {
            film.Ispisi();
            std::cout << std::endl;
            ima_zaduzenja = true;
        }
    }

    if (!ima_zaduzenja) {
        std::cout << "Korisnik nema zaduzenja!" << std::endl;
    }
}

int main ()
{
    Videoteka videoteka;
    try {
        videoteka.RegistrirajNovogKorisnika(1, "i1 p1", "a1", "1");
        videoteka.RegistrirajNovogKorisnika(2, "i2 p2", "a2", "2");
        videoteka.RegistrirajNovogKorisnika(3, "i3 p3", "a3", "3");
        videoteka.RegistrirajNoviFilm(1, true, "Film 1", "Zanr 1", 2021);
        videoteka.RegistrirajNoviFilm(2, false, "Film 2", "Zanr 2", 2000);
        videoteka.RegistrirajNoviFilm(3, true, "Film 3", "Zanr 3", 1995);       
        std::cout << "Korisnici:\n";
        videoteka.IzlistajKorisnike();
        std::cout << std::endl;   
        std::cout << "Filmovi:\n";
        videoteka.IzlistajFilmove();
        std::cout << std::endl;
        videoteka.ZaduziFilm(1, 1);  
        videoteka.ZaduziFilm(2, 2);  
        videoteka.RazduziFilm(1);    
        videoteka.ZaduziFilm(3, 3);  
        std::cout << "Zaduzenja za korisnika 3:\n";
        videoteka.PrikaziZaduzenja(3);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Greska: " << e.what() << std::endl;
    }

	return 0;
}
