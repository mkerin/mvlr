#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "functions.hpp"

Eigen::MatrixXi readMatrix(const char file_path[], Eigen::Ref<Eigen::MatrixXi> X, bool header){
  /* read in integer valued matrix from txt file in file_path.
   * 2nd parameter is used for function overloading only.
   * This method would beenfit from return value optimisation.
   */
  std::ifstream infile;
  std::string line;
  std::vector<int> values;
  int rows = 0;
  
  infile.open(file_path);
  if(header) getline(infile, line); // ignore first line is header exists
  if(!infile.is_open()) {
    std::cout << "File not found" << std::endl;
    return X;
  }
  else {
    while(getline(infile, line)){
      std::stringstream lineStream(line);
      int tmp;
      while(lineStream >> tmp){
        values.push_back(tmp);
      }
      rows++;
    }

    Eigen::Map<Eigen::MatrixXi> M_tmp(values.data(), values.size() / rows, rows);
    Eigen::MatrixXi M(values.size() / rows, rows);
    //M = Eigen::MatrixXi::Zero(values.size() / rows, rows);
    M << M_tmp;
    M.transposeInPlace();
    
    printf("Matrix of dim (%li, %li) read from file %s. \n", M.rows(), M.cols(), file_path);
    return M;
  }
}

Eigen::MatrixXd readMatrix(const char file_path[], Eigen::Ref<Eigen::MatrixXd> X, bool header){
  /* read in integer valued matrix from txt file in file_path.
   * 2nd parameter is used for function overloading only.
   * This method would benefit from return value optimisation.
   *
   * If an NA is detected in a column store the index in invalid_cols.
   * Then remove the whole column from the matrix at the end.
   *
   *
   */
  std::ifstream infile;
  std::string line;
  std::vector<double> values;
  int rows = 0;
  
  infile.open(file_path);
  if(header) getline(infile, line); // ignore first line is header exists
  if(!infile.is_open()) {
    std::cout << "File not found" << std::endl;
    return X;
  }
  else {
    std::set<int> invalid_cols;
    std::string word, invalid1("NA"), invalid2("\"NA\"");
    while(getline(infile, line)){
      std::stringstream lineStream(line);
      double tmp;
      int curr_col = 0;
      
      while(! lineStream.eof()){
        word.clear();
        lineStream >> word;
        if( (!word.compare(invalid1)) || (!word.compare(invalid2)) ){
           // true if word == "NA"
          tmp = std::numeric_limits<double>::quiet_NaN();
          invalid_cols.insert(curr_col);
        } else {
          // if word is not NA (implied number)
          tmp = stod(word);
        }
        values.push_back(tmp);
        curr_col++;
      }
      rows++;
    }
    
    // set all NaN values to mean of their row
    int cols = values.size() / rows;
    std::set<int>::iterator it;
    for(it = invalid_cols.begin(); it != invalid_cols.end(); it++){
      // iterate through
      bool is_invalid_col;
      int n = 0;
      double mean, total = 0;
      for(int i = 0; i < values.size(); i++){
        is_invalid_col = ((i % (cols)) == *it);
        //printf("Index: %i, value: %f, row: %i, invalid: %i \n", i, values[i], (i % (cols)), *it);
        if(is_invalid_col && (!isnan(values[i]))){
          total += values[i];
          n++;
        }
      }
      
      if(n==0) mean = 0;
      else mean = total / n;
      
      for(int i = 0; i < values.size(); i++){
        is_invalid_col = ((i % (cols)) == *it);
        if(is_invalid_col && (isnan(values[i]))){
          values[i] = mean;
        }
      }
    }
    
    

    Eigen::Map<Eigen::MatrixXd> M_tmp(values.data(), values.size() / rows, rows);
    Eigen::MatrixXd M(values.size() / rows, rows);
    //M = Eigen::MatrixXi::Zero(values.size() / rows, rows);
    M << M_tmp;
    M.transposeInPlace();
    
    printf("Matrix of dim (%li, %li) read from file %s. \n", M.rows(), M.cols(), file_path);
    return M;
  }
}