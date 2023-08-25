// TP 2022/2023: Zadaća 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

int count(int broj) {
  int count = 0;
  bool neg = false;
  if (broj < 0) {
    broj = -broj;
    neg=true;
  }
  if (broj == 0)
    return 1;
  while (broj != 0) {
    broj = broj / 10;
    count++;
  }
  if (neg == true) {
    count++;
  }
  return count;
}
int maxSirina(std::vector<std::vector<int>> mat) {
  if (mat.size() == 0) {
    return 0;
  }
  int max = count(mat[0][0]);
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat.at(i).size(); j++) {
      if (count(mat.at(i).at(j)) > max) {
        max = count(mat.at(i).at(j));
      }
    }
  }
  return max;
}
std::vector<std::vector<int>> KreirajSpiralnu(int m, int n,  int k, bool orjen) {
  if (m <= 0 || n <= 0) {
    m = 0;
    n = 0;
    
  }
std::vector<std::vector<int>> mat(m, std::vector<int>(n));
int x=k;
if (mat.size()==0 || mat[0].size()==0) return mat;
int preth=k;

  if (orjen == true) {
    int p1 = 0, q1 = 0, p2 = m - 1, q2 = n - 1;
    while (k <= (k + m * n - 1) && p1 <= p2 && q1 <= q2) {
      for (int i = q1; i <= q2; i++) {
        mat.at(p1).at(i) = k++;

        if(preth>mat[p1][i]) throw std::logic_error("");
        preth=mat[p1][i];

      }
      for (int j = p1 + 1; j <= p2; j++) {
        mat.at(j).at(q2) = k++;

        if(preth>mat[j][q2]) throw std::logic_error("");
        preth=mat[j][q2];

      }
      if (p1 < p2) {
        for (int i = q2 - 1; i >= q1; i--) {
          mat.at(p2).at(i) = k++;

          if (preth>mat[p2][i]) throw std::logic_error("");
          preth=mat[p2][i];

        }
      }
      if (q1 < q2) {
        for (int j = p2 - 1; j >= p1 + 1; j--) {
          mat.at(j).at(q1) = k++;

          if (preth>mat[j][q1]) throw std::logic_error("");
          preth=mat[j][q1];

        }
      }

      p1++;
      p2--;
      q1++;
      q2--;
    }
  }
  preth=x;

  if (orjen == false) {
    int p1 = 0, q1 = 0, p2 = m - 1, q2 = n - 1;
    while (k <= k + m * n - 1 && p1 <= p2 && q1 <= q2) {

      for (int i = p1; i <= p2; i++) {
        mat.at(i).at(q1) = k++;

        if (preth>mat[i][q1]) throw std::logic_error("");
        preth=mat[i][q1];

      }
      for (int j = q1 + 1; j <= q2; j++) {
        mat.at(p2).at(j) = k++;

        if(preth>mat[p2][j]) throw std::logic_error("");
        preth=mat[p2][j];

      }
      if (q1 < q2) {
        for (int i = p2 - 1; i >= p1; i--) {
          mat.at(i).at(q2) = k++;

          if (preth>mat[i][q2]) throw std::logic_error("");
          preth=mat[i][q2];

        }
      }
      if (p1 < p2) {
        for (int j = q2 - 1; j >= q1 + 1; j--) {
          mat.at(p1).at(j) = k++;

          if (preth>mat[p1][j]) throw std::logic_error("");
          preth=mat[p1][j];
        }
      }
      p1++;
      p2--;
      q1++;
      q2--;
    }
  }
  return mat;
}
bool DaLiJeSpiralnaMatrica(std::vector<std::vector<int>>mat){
    try{
    if (mat==KreirajSpiralnu(mat.size(), mat[0].size(),mat[0][0] , true) || mat==KreirajSpiralnu(mat.size(), mat[0].size(), mat[0][0], false) ) {
       return true; 
    }
    }catch(std::logic_error &e){
        return false;
    }
    return false;
}

int main() {
  int m, n, k;
  char slovo;
  bool orjen=true;
  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> m >> n;
  std::cout << "Unesite pocetnu vrijednost: ";
  std::cin >> k;
  std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: ";
  std::cin >> slovo;
  if (slovo == 'D') {
    orjen = true;
  } else if (slovo == 'L') {
    orjen = false;
  }
  std::vector<std::vector<int>> mat = KreirajSpiralnu(m, n, k, orjen);
  std::cout << "Kreirana spiralna matrica: " << std::endl;
  int sirina = maxSirina(mat) + 1;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << std::setw(sirina) << mat.at(i).at(j);
    }
    std::cout << std::endl;
  }
  return 0;
}
