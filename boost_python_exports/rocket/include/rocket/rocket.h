#ifndef _ROCKET_H_
#define _ROCKET_H_

#include <Eigen/Core>

namespace rocket {

class Rocket {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Rocket();
  Rocket(double max_speed);
  Rocket(double max_speed, const Eigen::Matrix2d& inertia_matrix);
  virtual ~Rocket();

  double getMaxSpeed() const;
  void setMaxSpeed(double max_speed);

  void setInertiaMatrix(const Eigen::Matrix2d& inertia_matrix);
  Eigen::Matrix2d& getInertiaMatrix();
  const Eigen::Matrix2d& getInertiaMatrix() const;
  
  virtual std::string name() const = 0;
 private:
  double max_speed_;
  Eigen::Matrix2d inertia_matrix_;
};

class Booster : public Rocket {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  Booster();
  Booster(double max_speed, 
          const Eigen::Matrix2d& inertia_matrix,
          unsigned num_boosts);
  virtual ~Booster();

  unsigned getNumBoosts() const;
  void setNumBoosts(unsigned nb);

  virtual std::string name() const;  
 private:
  unsigned num_boosts_;
};

} // namespace rocket


#endif /* _ROCKET_H_ */
