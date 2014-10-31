MainControllerRTC
=================

Layout
----

![MainControllerRTC](https://farm8.staticflickr.com/7516/15043850714_ca575240e1_o.png)

Features
----
  * Receive the command state
  * Request the path
  * Decide the behaviour of Mobile Controller

Requirements
----
  * OS
   * Linux Distributions
   * Windows
  * Softwares
   * OpenRTM-aist C++ 1.1 or later
   * CMake 2.8

Port
----

| Name     | Type          | Data Type   | Purpose |
| -------- | ------------- | ----------- | ------- |
| command   | In       | RTC::TimedState | Enable recognition |
| current_pose  | In      | RTC::TimedPose2D  | The recognition result |
| target_velocity  | Out      | RTC::TimedVelocity2D   | The text to speech out     |
| target_pose | Out | RTC::TimedPose2D | The target pose of the robot  |
| path | Service | PathService | Get the calculated path of the robot  |

  * PathService.idl

| Function | Variable | Type | Data Type | Purpose |
| -------- | -------- | ---- | --------- | ------- |
| get_path | path     | out | RTC::Path2D | The found path |
|          | position | in  | RTC::Pose2D | The robot position |
|          | target   | in  | RTC::Pose2D | The target position |

Usage
----

| Command State | Purpose |
| ------------- | ------------|
| 1       | Go Forward  
| 2      | Go Backward 
| 3      | Turn Right  
| 4      | Turn Left 
| 5      | Stop
| 6      | Move to the saved position |
| 7      | Save the current position |

License
----

Licensed under the [Apache License, Version 2.0][Apache]  
Distributed under the [MIT License][mit].  
Dual licensed under the [MIT license][MIT] and [Apache License, Version 2.0][Apache].  
 
[Apache]: http://www.apache.org/licenses/LICENSE-2.0
[MIT]: http://www.opensource.org/licenses/mit-license.php
