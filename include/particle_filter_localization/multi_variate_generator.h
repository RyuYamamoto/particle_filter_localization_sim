#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#include <random>

class MultiVariateNormal
{
public:
  MultiVariateNormal(const Eigen::VectorXd mean, const Eigen::MatrixXd covariance)
    : mean_(mean), covariance_(covariance)
  {
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigen_solver(covariance_);
    transform_ = eigen_solver.eigenvectors() * eigen_solver.eigenvalues().cwiseSqrt().asDiagonal();
  }
  Eigen::VectorXd operator()() const
  {
    static std::random_device seed;
    static std::mt19937 engine(seed());
    static std::normal_distribution<> dist;

    return mean_ + transform_ * Eigen::VectorXd{mean_.size()}.unaryExpr([&](auto x) { return dist(engine); });
  }
  void setMean(const Eigen::VectorXd mean){mean_ = mean;}
  void setCovariance(const Eigen::MatrixXd covariance){covariance_ = covariance;}

private:
  Eigen::VectorXd mean_;
  Eigen::MatrixXd covariance_;
  Eigen::MatrixXd transform_;
};
