-- Lua Control Script
-- Reloads each time the pendulum resets, so
-- you can test your code rapidly!
kP = 0
kI = 0
kD = 0

previousError = 0
sum = 0 
goal = 0

function setup()
  kP = -0.3
  kI = 0
  kD = -0.005

  sum = 0
  previousError = 0
end

function calculate(dt, input)
  error = goal - input
  derror = (error - previousError) / dt
  sum = sum + error * dt

  output = kP * error + kI * sum + kD * derror

  previousError = error
  return output
end