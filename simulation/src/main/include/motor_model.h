#pragma once

// Simple motor model
class motor_model {
 public:
  motor_model(double freespeed, double freecurrent, double stalltorque, double stallcurrent)
      : _free_speed(freespeed),
        _free_current(freecurrent),
        _stall_torque(stalltorque),
        _stall_current(stallcurrent) {}

  inline double internal_resistance() const { return _v_nom / _stall_current; }
  inline double kv() const { return (_v_nom - _free_current * _v_nom / _stall_current) / _free_speed; }
  inline double kt() const { return _stall_current / _stall_torque; }

  double nominal_voltage() const { return _v_nom; }

  double get_current(double voltage, double speed) const {
    // V_w = kv * w
    double vel_voltage = kv() * speed;
    // V = IR + kv*w = IR + V_vel
    // I = (V - V_vel) / R
    return (voltage - vel_voltage) / internal_resistance();
  }

  double get_torque(double current) const {
    // I = kt * t, t = I / kt
    return current / kt();
  }

  double get_acceleration(double torque, double radius, double mass) const {
    // a = T / r / m
    return torque / radius / mass;
  }

  double get_acceleration(double voltage, double speed, double radius, double mass) const {
    return get_acceleration(get_torque(get_current(voltage, speed)), radius, mass);
  }

 private:
  double _v_nom = 12;
  double _free_speed, _free_current;
  double _stall_torque, _stall_current;
};