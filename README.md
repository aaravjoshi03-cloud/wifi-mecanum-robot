Wi-Fi Controlled Mecanum Wheel Robot

A 4-wheel mecanum drive robot controlled wirelessly from a phone over Wi-Fi. Built with an ESP32 and L298N motor drivers. Mecanum wheels let the robot move forward, backward, sideways, diagonally, and rotate in place without turning the chassis first.

Status: Prototype built and demonstrated. The hardware has since been dismantled; this repo documents the design, build, and results.

Demo

https://youtu.be/DVnm_fAcJ20?si=CbebYvSV3-WPDLrn

Note on the demo videos: The robot is controlled wirelessly over Wi-Fi from a phone. The cable visible in the videos is only a power cable for the ESP32 (USB power). It does not carry any control signals. All driving commands are sent over Wi-Fi.

Features
Omnidirectional movement: forward, backward, strafe left/right, diagonal, and rotation in place
Wireless control from a phone over Wi-Fi
ESP32 as the main controller
Four independently driven motors
Hardware
Component	Details
Controller	ESP32
Motors	4 x BO motors
Motor drivers	L298N driver boards
Wheels	4 x mecanum wheels
Chassis	Custom/black base plate
Motor power	Battery pack
ESP32 power	USB power cable (power only, no data/control)
How It Works

Each mecanum wheel has rollers set at 45 degrees. By changing the direction and speed of each of the four wheels, the robot can move in any direction:

Motion	Wheel pattern (FL, FR, RL, RR)
Forward	all wheels forward
Backward	all wheels backward
Strafe right	FL +, FR -, RL -, RR +
Strafe left	FL -, FR +, RL +, RR -
Rotate in place	left side forward, right side backward (or the reverse)

(FL = front left, FR = front right, RL = rear left, RR = rear right. Exact signs depend on how the motors are wired.)

The phone connects to the ESP32 over Wi-Fi and sends movement commands. The ESP32 translates each command into direction and speed signals for the L298N drivers, which drive the four motors.

Control Flow
Phone (Wi-Fi) -> ESP32 -> L298N drivers -> 4 BO motors -> mecanum wheels
Build Notes
Originally planned around a Makeblock MegaPi board, but switched to an ESP32 with L298N drivers.
The ESP32 was powered through a USB cable during testing, separate from the motor battery supply.
Share a common ground between the ESP32 and the motor drivers so control signals work correctly.
Challenges and What I Learned
Switching controller boards mid-project and re-planning the wiring
Getting all four wheels to drive in the correct direction for each motion
Mecanum wheels can drift when moving sideways. A future version would add sensor feedback to correct this
Future Improvements
Power the ESP32 from the onboard battery (using a buck converter) so the robot is fully untethered
Add an IMU and wheel encoders for odometry and drift correction
Add PID control so the robot drives straight and holds position
Add a camera or distance sensors for autonomous behavior such as object following or obstacle avoidance
Simulate the kinematics in ROS 2 / Gazebo before testing on hardware
Author

Aarav Joshi B.Tech Mechatronics, NMIMS Mumbai
