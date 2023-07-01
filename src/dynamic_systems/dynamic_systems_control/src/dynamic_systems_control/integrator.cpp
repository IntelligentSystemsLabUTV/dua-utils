/**
 * Dynamic systems library base class.
 *
 * Giorgio Manca <giorgio.manca.97@gmail.com>
 * Intelligent Systems Lab <isl.torvergata@gmail.com>
 *
 * June 29, 2023
 */

#include <dynamic_systems_control/integrator.hpp>

namespace DynamicSystems
{
  namespace Control 
  {
    /* InitParams */

    IntegratorInitParams::~IntegratorInitParams() {}

    std::unique_ptr<InitParams> IntegratorInitParams::clone() const {
      std::unique_ptr<IntegratorInitParams> res = std::make_unique<IntegratorInitParams>();
      res->copy(*this);
      return res;
    }

    void IntegratorInitParams::copy(const InitParams &other) {
      InitParams::copy(other);
      auto casted = dynamic_cast<const IntegratorInitParams&>(other);
      this->time_sampling = casted.time_sampling;
      this->rows = casted.rows;
      this->cols = casted.cols;
    }


    /* SetupParams */

    IntegratorSetupParams::~IntegratorSetupParams() {}

    std::unique_ptr<SetupParams> IntegratorSetupParams::clone() const {
      std::unique_ptr<IntegratorSetupParams> res = std::make_unique<IntegratorSetupParams>();
      res->copy(*this);
      return res;
    }

    void IntegratorSetupParams::copy(const SetupParams &other) {
      SetupParams::copy(other);
      auto casted = dynamic_cast<const IntegratorSetupParams&>(other);
      this->multiplier = casted.multiplier;
      this->saturation = casted.saturation;
    }


    /* State */

    IntegratorState::~IntegratorState() {}

    std::unique_ptr<State> IntegratorState::clone() const {
      std::unique_ptr<IntegratorState> res = std::make_unique<IntegratorState>();
      res->copy(*this);
      return res;
    }

    void IntegratorState::copy(const State &other) {
      State::copy(other);

      auto casted = dynamic_cast<const IntegratorState&>(other);
      this->x = casted.x;
    }
    

    /* System */

    void IntegratorSystem::init_parse(const InitParams& initParams) {
      auto casted = dynamic_cast<const IntegratorInitParams&>(initParams);

      if(casted.time_sampling < 0.0) {
        throw std::invalid_argument("Invalid sampling time for integrator system.");
      }

      if(casted.time_sampling > 0.0) {
        this->kt_ = casted.time_sampling;
      } else {
        this->kt_ = 1.0;
      }

      std::shared_ptr<IntegratorState> state = std::make_shared<IntegratorState>();
      state->x = MatrixXd(casted.rows, casted.cols);
      reset(state);
      input(MatrixXd(casted.rows, casted.cols));
      update();
    }

    void IntegratorSystem::setup_parse(const SetupParams& setupParams) {
      auto casted = dynamic_cast<const IntegratorSetupParams&>(setupParams);

      if(casted.saturation < 0.0) {
        throw std::invalid_argument("Invalid saturation for integrator system.");
      }
      
      this->mul_ = casted.multiplier;
      this->sat_ = casted.saturation;
    }

    void IntegratorSystem::setup_default() {
      this->mul_ = 1.0;
      this->sat_ = 1.0;
    }

    void IntegratorSystem::deinit(){}

    void IntegratorSystem::state_validator(State &state) {
      IntegratorState &state_casted = static_cast<IntegratorState&>(state);
      if(this->sat_ > 0.0) {
        state_casted.x = state_casted.x.cwiseMax(-this->sat_).cwiseMin(this->sat_);
      }
    }

    void IntegratorSystem::input_validator(const State &state, MatrixXd &input) {
      const IntegratorState &state_casted = static_cast<const IntegratorState&>(state);
      if(input.size() != state_casted.x.size()) {
        throw std::invalid_argument("Invalid input size.");
      }
    }

    void IntegratorSystem::dynamic_map(const State &state, const MatrixXd &input, State &next) {
      const IntegratorState &state_casted = static_cast<const IntegratorState&>(state);
      IntegratorState &next_casted = static_cast<IntegratorState&>(next);
      next_casted.x = state_casted.x + this->mul_ * this->kt_ * input;
    }

    void IntegratorSystem::output_map(const State &state, const MatrixXd &input, MatrixXd& output) {
      UNUSED(input);
      const IntegratorState &state_casted = static_cast<const IntegratorState&>(state);
      output = state_casted.x;
    }
  }
} 