//TP 2022/2023: Zadaća 3, Zadatak 3
#include <exception>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <new>

template <typename el_tip>
struct Matrica{
    char ime_matrice;
    int br_redova,br_kolona;
    el_tip**elementi=nullptr;
};

template<typename el_tip>
void UnistiMatricu(Matrica<el_tip> &mat){
    if (mat.elementi==nullptr) return; ///////
    for(int i=0; i<mat.br_redova; i++) delete []mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi=nullptr;
}
template <typename el_tip>
Matrica<el_tip>StvoriMatricu(int m, int n, char name=0){
    Matrica<el_tip> mat;
    mat.br_redova=m;
    mat.br_kolona=n;
    mat.ime_matrice=name;
    mat.elementi=new el_tip*[m]{};
    try{
        for (int i=0; i<m; i++){
            mat.elementi[i]=new el_tip[n];
        }
    }catch(...){
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template<typename el_tip>
void UnesiMatricu(Matrica<el_tip> &mat){
    for (int i=0; i<mat.br_redova; i++){
        for (int j=0; j<mat.br_kolona; j++){
            std::cout<<mat.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>mat.elementi[i][j];
        }
    }
}
template<typename el_tip>
void IspisiMatricu( const Matrica<el_tip> &mat, int setw, int preciznost=6 , bool treba_brisati=false){
   
    for (int i=0; i<mat.br_redova; i++){
        for (int j=0; j<mat.br_kolona; j++){
            std::cout<<std::setprecision(preciznost)<<std::setw(setw)<<mat.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    //  if (treba_brisati){
    //     UnistiMatricu(mat);
    //     return;
    // } 
}

template<typename el_tip>
Matrica<el_tip> ZbirMatrica(const Matrica<el_tip> &m1, const Matrica< el_tip> &m2){
    if (m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");

    auto m3=StvoriMatricu<el_tip>( m1.br_redova, m1.br_kolona);
    for (int i=0; i<m1.br_redova; i++){
        for (int j=0; j<m1.br_kolona; j++){
            m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
        }
    }
    return m3;
}
template <typename el_tip>
Matrica<el_tip> ProduktMatrica(const Matrica<el_tip> &m1, const Matrica<el_tip> &m2){
    if (m2.br_redova!= m1.br_kolona) throw std::domain_error("Matrice nisu saglasne za mnozenje");

    auto m3=StvoriMatricu<el_tip>(m1.br_redova,m2.br_kolona);

    for (int i=0; i<m1.br_redova; i++){
        for (int j=0; j<m2.br_kolona; j++){
            double sum=0;
            for (int k=0; k<m2.br_redova; k++) sum+= m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=sum;
        }
    }
    return m3;
}
template <typename el_tip>
Matrica<el_tip> MatricniHarmonijskiPolinom(const Matrica<el_tip>& mat, int n){
    if (mat.br_kolona!=mat.br_redova) throw std::domain_error("Matrica nije kvadratna");
    if (n<0) throw std::domain_error("Pogresan parametar n");

    auto nova=StvoriMatricu<el_tip>(mat.br_redova,mat.br_redova);
    auto stepenovana=StvoriMatricu<el_tip>(mat.br_redova, mat.br_redova);
    nova=mat;
    stepenovana=mat;
    auto trenutna=StvoriMatricu<el_tip>(mat.br_redova, mat.br_redova);

    for (int i=2; i<=n; i++){
        stepenovana =ProduktMatrica(stepenovana,mat );
        for (int j=0; j<mat.br_redova; j++){
            for (int k=0; k<mat.br_kolona; k++){
                trenutna.elementi[j][k]= 1.*stepenovana.elementi[j][k]/i;   
                        }
        }
        nova=ZbirMatrica(nova, trenutna);

    }
UnistiMatricu(trenutna);
UnistiMatricu(stepenovana);
 
    return nova;
}
int main ()
{

int m;
int red;
Matrica<double> a,mh;

std::cout<<"Unesite dimenziju kvadratne matrice: "<<std::endl;
std::cin>>m;
try{
    mh=StvoriMatricu<double>(m, m);
    a = StvoriMatricu<double>(m, m, 'A');
    std::cout<<"Unesite elemente matrice A: "<<std::endl;
    UnesiMatricu(a);
    std::cout<<"Unesite red polinoma: "<<std::endl;
    std::cin>>red;
    std::cout<<"Matricni harmonijski polinom:"<<std::endl;
    mh= MatricniHarmonijskiPolinom(a, red);
    IspisiMatricu(mh, 10);
}catch(std::bad_alloc) {
 std::cout << "Nema dovoljno memorije!\n";
}
UnistiMatricu(mh);
UnistiMatricu(a);


	return 0;
}
