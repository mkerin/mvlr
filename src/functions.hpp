// Prototypes
void genData(int n, int x, int t);
void writeMatrix(const char file_name[], Eigen::Ref <const Eigen::MatrixXi> M);
void writeMatrix(const char file_name[], Eigen::Ref <const Eigen::MatrixXd> M);
Eigen::MatrixXi readMatrix(const char file_path[], Eigen::Ref<Eigen::MatrixXi> X, bool header);
Eigen::MatrixXd readMatrix(const char file_path[], Eigen::Ref<Eigen::MatrixXd> X, bool header);
Eigen::MatrixXd centerMat(Eigen::Ref<Eigen::MatrixXd> M);