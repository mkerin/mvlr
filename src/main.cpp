// Handwritten project outside of CLion.
/* cmake . -Bbuild
* cmake --build build
* ./bin/main
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>
#include <random>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>

// My functions
#include "functions.hpp"

// IMPROVEMENTS

int main (int argc, char *argv[]) {
  char env_filepath[40], trait_filepath[40], res_filepath[40];
  Eigen::MatrixXd X, Y, R, y_hat;
  bool header_in_file = true;
  
  // command line arguments
  if(argc > 1){
    strcpy(env_filepath, argv[1]);
    strcpy(trait_filepath, argv[2]);
  }
  else {
    strcpy(env_filepath, "data/for_matt_env.tab");
    strcpy(trait_filepath, "data/for_matt_trait.tab");
  }
  
  if(argc > 3) strcpy(res_filepath, argv[3]);
  else strcpy(res_filepath, "data/mvlr_coefficients.txt");
  
  // reading data from file
  X = readMatrix(env_filepath, X, header_in_file);
  Y = readMatrix(trait_filepath, Y, header_in_file);
  std::cout << "\nPrinting X" << std::endl;
  std::cout << X << std::endl;
  
  // center and scale
  
  Eigen::RowVectorXd means = X.colwise().sum() / X.rows();
  std::cout << "\nPrinting means" << std::endl;
  std::cout << means << std::endl;
  X.rowwise() -= means;
  std::cout << "\nPrinting X" << std::endl;
  std::cout << X << std::endl;
  
  Eigen::MatrixXd covs;
  if(X.rows() > 1){
    /*
    std::cout << "\nPrinting sqs" << std::endl;
    std::cout << (X.array() * X.array()) << std::endl;
    
    std::cout << "\nPrinting sum of sqs" << std::endl;
    std::cout << (X.array() * X.array()).colwise().sum() << std::endl;
    */
    covs = (X.array() * X.array()).colwise().sum() / (X.rows() - 1);
  } else {
    covs = (X.array() * X.array()).colwise().sum() / (X.rows());
  }
  
  //std::cout << "\nPrinting covs" << std::endl;
  //std::cout << covs << std::endl;
  
  Eigen::MatrixXd sds = covs.array().sqrt();
  //std::cout << "\nPrinting sds" << std::endl;
  //std::cout << sds << std::endl;
  
  for(int i = 0; i < sds.size(); i++){
    if(*(sds.data() + i) != 0) *(sds.data() + i) = 1 / *(sds.data() + i);
  }
  std::cout << "\nPrinting sds" << std::endl;
  std::cout << sds << std::endl;
  
  X = (X * sds.asDiagonal()).eval();
  std::cout << "\nPrinting X" << std::endl;
  std::cout << X << std::endl;
  
  
  // performing mvlr
  printf("X: (%li, %li) \n", X.rows(), X.cols());
  R = X.transpose() * X;
  y_hat = X.transpose() * Y;
  Eigen::MatrixXd beta_hat = R.ldlt().solve(y_hat);
  //Eigen::MatrixXd beta_hat = Eigen::MatrixXd::Zero(X.rows(), X.cols());
  
  
  // Output to console.
  std::vector<std::string> covariates, traits;
  std::string line, word;
  std::stringstream lineStream;
  
  std::ifstream infile(env_filepath);
  if(infile.is_open()){
    getline(infile, line);
    lineStream.str(line);
    puts(line.c_str());
    while(lineStream >> word){
      covariates.push_back(word);
      puts(word.c_str());
    }
    lineStream.clear();
    infile.close();
  }
  infile.open(trait_filepath);
  if(infile.is_open()){
    getline(infile, line);
    lineStream.str(line);
    puts(line.c_str());
    while(lineStream >> word){
      traits.push_back(word);
      puts(word.c_str());
    }
    lineStream.clear();
    infile.close();
  }
  
  std::cout << beta_hat << std::endl;
  
  Eigen::MatrixXd::Index maxRow, maxCol;
  //beta_hat.colwise().maxCoeff(&maxRow, &maxCol);
  std::cout << "Max elements in row: " << beta_hat.colwise().maxCoeff() << std::endl;
  
  std::vector<Eigen::MatrixXd::Index> maxRows(beta_hat.cols());
  std::vector<double> maxVals(beta_hat.cols());
  for(int c = 0; c < beta_hat.cols(); c++){
    maxVals[c] = beta_hat.col(c).maxCoeff(&(maxRows[c]));
    printf("Max regression coefficient for trait %s is (%s, %f) \n",
           traits[c].c_str(), covariates[maxRows[c]].c_str(), maxVals[c]);
  }
  
  /*
  std::vector<std::string>::iterator it;
  for(it = traits.begin(); it != traits.end(); it++) std::cout << *it << " ";
  std::cout << std::endl;
  for(it = covariates.begin(); it != covariates.end(); it++) std::cout << *it << " ";
  std::cout << std::endl;
  */
  // saving output to file.
  infile.open(env_filepath);
  std::ofstream outfile(res_filepath);
  if(infile.is_open() && outfile.is_open()){
    std::string line;
    getline(infile, line);
    outfile << line << std::endl;
    beta_hat.transposeInPlace();
    outfile << beta_hat << std::endl;
    outfile.close();
  }
  
  return 0;
}


