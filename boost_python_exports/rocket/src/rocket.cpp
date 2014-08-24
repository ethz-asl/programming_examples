#include <rocket/rocket.h>

namespace rocket {
Rocket::Rocket() : 
max_speed_(100.0), inertia_matrix_(Eigen::Matrix2d::Identity()) {

}

Rocket::Rocket(double max_speed) : 
max_speed_(max_speed), inertia_matrix_(Eigen::Matrix2d::Identity()) {

}

Rocket::Rocket(double max_speed, const Eigen::Matrix2d& inertia_matrix) : 
max_speed_(max_speed), inertia_matrix_(inertia_matrix) {

}

Rocket::~Rocket() {

}


double Rocket::getMaxSpeed() const {
  return max_speed_;
}

void Rocket::setMaxSpeed(double max_speed) {
  max_speed_ = max_speed;
}


void Rocket::setInertiaMatrix(const Eigen::Matrix2d& inertia_matrix) {
  inertia_matrix_ = inertia_matrix;
}

Eigen::Matrix2d& Rocket::getInertiaMatrix() {
  return inertia_matrix_;
}

const Eigen::Matrix2d& Rocket::getInertiaMatrix() const {
  return inertia_matrix_;
}


Booster::Booster() {

}

Booster::Booster(double max_speed, 
                 const Eigen::Matrix2d& inertia_matrix,
                 unsigned num_boosts) :
    Rocket(max_speed, inertia_matrix), num_boosts_(num_boosts){

}

Booster::~Booster() {

}

unsigned Booster::getNumBoosts() const {
  return num_boosts_;
}

void Booster::setNumBoosts(unsigned nb) {
  num_boosts_ = nb;
}

std::string Booster::name() const {
  return "Booster";
}

} // namespace rocket
