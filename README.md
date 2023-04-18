# **Disclaimer**:
This is a project showcase for my Design Thinking Innovation course project during my university education at SUTD. This is my first actual experience with embeded software programming. The projected utilized both hardware and software knowledge for prototyping. See below for the progress of the project.

# **BinChillin**:
<p align="center">
  <img width="500" src='assets/main_bin.png'>
</p>
<p align="center">
  Image of the bin
</p>

<p align="center">
  <img width="500" src='assets/slider2.png'>
</p>

BINCHILLIN is a next generation smart IOT bin. The bin can add an interactive element and gamify throwing of the trash. While inspiring people to clean up after themselves, it utilizes light to add colours to create inviting and relaxing spaces for the user. The bin encompasses the concept that something mundane and often overlooked like the rubbish bin can be transformed into something that is beautiful for the user using design thinking and analysis.

# **Context**:
BinChillin was created as part of SUTD's 03.007 project. The project required us to do a detailed analysis of a site and think of ways to improve the area. 

<p align="center">
  <img width="500" src='assets/site_pic.png'>
</p>
Chosen location is outside Singapore Expo MRT.

<p align="center">
  <img width="500" src='assets/trash_site.png'>
</p>

<p align="center">
  <img width="500" src='assets/trash_sampling.png'>
</p>

For our group, we analysed the site and realised that it is filled with trash. We hoped that we could create something that can inspire people to throw trash themselves.

<p align="center">
  <img width="500" src='assets/traffic_flow.png'>
</p>

After analysing the traffic flow, we could obtain data so that we were able to design solutions that has maximum impact.

# **Hardware**

<p align="center">
  <img width="500" src='assets/bin_internal.png'>
</p>

<p align="center">
  <img width="500" src='assets/DTI_MAIN_CIRCUIT.png'>
</p>

<p align="center">
  <img width="500" src='assets/creating_grid.jpeg'>
</p>

For the hardware, the whole bin is powered by Arduino powered by a 5V Power Supply Unit. The LEDs used to create the grid is WS2812B.

# **GamePlay**

<p align="center">
  <img width="500" src='assets/screen_design.png'>
</p>

The game consists of moving platforms and a ball idling on the top. The user will have to time their throw of the trash such that the ball drops to the bottom without touching any of the walls. The user will receive a reward from the machine if their ball successfully reach the bottom.

# **Finite State Machine**

<p align="center">
  <img width="500" src='assets/State_Machine_Diagram.png'>
</p>

FSM concept was used to represent the states of the game for logic control.

# **Bit Operation**
To improve the refresh rate for the game, bit control was used to represent the game state so that it does not take up majority of the CPU access.

# **Prototype Testing**
For the testing of our prototype, we conducted both virtual and physical testing.

<p align="center">
  <img width="500" src='assets/5cm-6.png'>
</p>

virtual testing allowed us to have the best specification of the bin for the target audience.

<p align="center">
  <img width="500" src='assets/5cm-3.png'>
</p>

We utilised physical prototypes to test the perfect pixel size for our LED.

# **User Validation**
<p align="center">
  <img width="500" src='assets/user_validation.png'>
</p>

For the user validation, we received majority positve reviews. This indicated that the design was a success. 

# **Conclusion**
Design Thinking Innovation course is not a technical course. It teaches us how to be creative design innovators to create solutions after a detailed analysis of a problem.
