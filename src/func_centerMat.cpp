#include <Eigen/Dense>

Eigen::MatrixXd centerMat(Eigen::Ref<Eigen::MatrixXd> M){
	// function to center and scale matrix M
	Eigen::RowVectorXd means = M.colwise().sum() / M.rows();
	M.rowwise() -= means;
	
	Eigen::MatrixXd covs;
	if(M.rows() > 1){
	  covs = (M.array() * M.array()).colwise().sum() / (M.rows() - 1);
	} else {
	  covs = (M.array() * M.array()).colwise().sum() / (M.rows());
	}
	
	Eigen::MatrixXd sds = covs.array().sqrt();
	
	for(int i = 0; i < sds.size(); i++){
	  if(*(sds.data() + i) != 0) *(sds.data() + i) = 1 / *(sds.data() + i);
	}
	
	M = (M * sds.asDiagonal()).eval();
	
	return M;
}