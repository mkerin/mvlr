#include <iostream>
#include <Eigen/Dense>
#include <fstream>

void writeMatrix(const char file_path[], const Eigen::Ref<const Eigen::MatrixXd> M){
  // function to write matrix M to file file_path
  std::ofstream file(file_path);
  if(file.is_open()){
    std::cout << "Saving matrix to file " << file_path << std::endl;
    file << M;
    file.close();
  }
}

void writeMatrix(const char file_path[], const Eigen::Ref<const Eigen::MatrixXi> M){
  // function to write matrix M to file file_path
  std::ofstream file(file_path);
  if(file.is_open()){
    std::cout << "Saving matrix to file " << file_path << std::endl;
    file << M;
    file.close();
  }
}
