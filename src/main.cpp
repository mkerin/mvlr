// Handwritten project outside of CLion.
/* cmake . -Bbuild
* cmake --build build
* ./bin/main
*/

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <random>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>

// My functions
#include "functions.hpp"

// IMPROVEMENTS

int main (int argc, char *argv[]) {
  
  
  Eigen::MatrixXd X, Y, R, y_hat;
  bool header = true;
  //X = readMatrix("data/biobank_env.tab", X, header);
  //Y = readMatrix("data/biobank_trait.tab", Y, header);
  
  X = readMatrix("data/for_matt_env.tab", X, header);
  Y = readMatrix("data/for_matt_trait.tab", Y, header);
  
  std::cout << X << std::endl;
  std::cout << Y << std::endl;
  
  R = X.transpose() * X;
  y_hat = X.transpose() * Y;
  
  Eigen::MatrixXd beta_hat = R.ldlt().solve(y_hat);
  std::cout << beta_hat << std::endl;
  
  /*
  if(argc >= 1 && !strcmp(argv[1], "new")){
    int n = atoi(argv[2]);
    int g = atoi(argv[3]);
    int t = atoi(argv[4]);
    genData(n, g, t);
  }
  
  // Reading in Matrix
  Eigen::MatrixXi X;
  Eigen::MatrixXd T, Y;
  X = readMatrix("data/X_mat.txt", X);
  Y = readMatrix("data/Y_mat.txt", Y);
  T = readMatrix("data/T_mat.txt", T);
  
  
  // Quick look at data
  std::cout << "Top left of X from file is: " << std::endl << X.topLeftCorner(5,5) << std::endl;
  std::cout << "Top left of T from file is: " << std::endl << T.topLeftCorner(5,5) << std::endl;
  
  // MVLR of environmental covariates only
  // b = (t(T)*T)^{-1}*t(T)*Y
  Eigen::VectorXd beta, y_hat;
  Eigen::MatrixXd R;
  
  R = X.transpose() * X;
  y_hat = X.transpose() * Y;
  
  MatrixXd beta_hat = R.ldlt().solve(y_hat);
  
  
  beta = R.colPivHouseholderQr().solve(y_hat);
  std::cout << "After using the colPivHouseholder, the first entries of beta are: " << std::endl << beta.topLeftCorner(5,1) << std::endl;  
  
  beta = R.inverse() * y_hat;
  std::cout << "After using brute force, the first entries of beta are:" << std::endl << beta.topLeftCorner(5,1) << std::endl;
  
  beta = R.llt().solve(y_hat);
  std::cout << "After using llt method, the first entries of beta are: " << std::endl << beta.topLeftCorner(5,1) << std::endl;  
  */
   
  
  return 0;
}


