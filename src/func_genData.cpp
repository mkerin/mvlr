#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <fstream>
#include "functions.hpp"

void genData(int n, int x, int t){
  // Function to generate new simulated data matrices X, T, Y, and write to file.
  std::cout << "Generating simulated data, with "
            << n << " individuals, "
            << x << " genes and "
            << t << " enviornmental covariates." << std::endl;
  std::ofstream file;
  double num, p_x;
  
  // RNG
  std::random_device rd;
  std::mt19937 mt(rd());
  

  Eigen::MatrixXi X = Eigen::MatrixXi(n, x); // SNP-count : Ber(p_x);
  Eigen::MatrixXd T = Eigen::MatrixXd::Random(n, t); // environmental covariates : N(0, theta_t);
  Eigen::MatrixXd Y = Eigen::MatrixXd::Random(n,1); // phenotype : N(0, theta_y);
  
  // Fill genetic matrix X with {0, 1, 2} w/p {1 - 2*p_x - p_x^2, 2*p_x, p_x^2}
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  p_x = 0.3; // Minor Allele Frequency
  
  for(int i = 0, nCols = X.cols(), nRows = X.rows(); i < nRows; i++){
    for(int j = 0; j < nCols; j++){
      num = distribution(mt);
      if(num < p_x * p_x) X(i, j) = 2;
      else if(num < p_x * (p_x + 2)) X(i, j) = 1;
      else X(i, j) = 0;
    }
  }
  
  std::cout << "Top left of X before file is: " << std::endl << X.topLeftCorner(5,5) << std::endl;
  std::cout << "Top left of T before file is: " << std::endl << T.topLeftCorner(5,5) << std::endl;
  
  // Write to file.
  writeMatrix("data/X_mat.txt", X);
  writeMatrix("data/T_mat.txt", T);
  writeMatrix("data/Y_mat.txt", Y);
}