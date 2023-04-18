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
<p align="center">
  Rendered image of the solution.
</p>

BINCHILLIN is a next generation smart IOT bin. The bin can add an interactive element and gamify throwing of the trash. While inspiring people to clean up after themselves, it utilizes light to add colours to create inviting and relaxing spaces for the user. The bin encompasses the concept that something mundane and often overlooked like the rubbish bin can be transformed into something that is beautiful for the user using design thinking and analysis.

# **Context**:
BinChillin was created as part of SUTD's 03.007 project. The project required us to do a detailed analysis of a site and think of ways to improve the area. Below shows some of my group's analysis of the site.

<p align="center">
  <img width="500" src='assets/site_pic.jpg'>
</p>
<p align="center">
  Chosen location is outside Singapore Expo MRT
</p>

<p align="center">
  <img width="500" src='assets/trash_site.jpg'>
</p>
<p align="center">
  Trash seen at the location.
</p>

<p align="center">
  <img width="500" src='assets/trash_sampling.png'>
</p>
<p align="center">
  Data sampling from walking around the location and counting the trash.
</p>

For our group, we analysed the site and realised that it is filled with trash. We hoped that we could create something that can inspire people to throw trash themselves. The site also has a dull lighting at night. There is a potential to utilize light to our advantage.

<p align="center">
  <img width="500" src='assets/traffic_flow.png'>
</p>
<p align="center">
  Traffic flow of different age groups from 6pm-730pm.
</p>

After analysing the traffic flow, we could obtain data so that we were able to design solutions that has maximum impact. We notice that from 6pm to 730pm, the majority of the users at the location are office workers. This adds a design consideration. Can we create something that will attract their attention?

# **Solution**:
We came out with the solution of BinChillin. The bin inspires users to throw trash via a gamified trash throwing system. The bin also utilized light to highlight itself at night. The game is designed in retro style so that the office workers will be attracted to the product. The game on the bin is created using very pixelated grid screen.

# **Hardware**

<p align="center">
  <img width="500" src='assets/bin_internal.png'>
</p>
<p align="center">
  The internal circuit of the bin.
</p>

<p align="center">
  <img width="500" src='assets/DTI_MAIN_CIRCUIT.png'>
</p>
<p align="center">
  The internal circuit of the bin.
</p>

<p align="center">
  <img width="500" src='assets/creating_grid.jpeg'>
</p>
<p align="center">
  Creation of pixelated grid system.
</p>

For the hardware, the whole bin is powered by Arduino powered by a 5V Power Supply Unit. The LEDs used to create the grid is WS2812B.

# **GamePlay**

<p align="center">
  <img width="500" src='assets/screen_design.png'>
</p>
<p align="center">
  The design of the grid system.
</p>

The game consists of moving platforms and a ball idling on the top. The user will have to time their throw of the trash such that the ball drops to the bottom without touching any of the walls. The user will receive a reward from the machine if their ball successfully reach the bottom.

# **Finite State Machine**

<p align="center">
  <img width="500" src='assets/State_Machine_Diagram.png'>
</p>
<p align="center">
  Finite State Diagram.
</p>

FSM concept was used to represent the states of the game for logic control.

# **Bit Operation**
To improve the refresh rate for the game, bit control was used to represent the game state so that it does not take up majority of the CPU access.

# **Prototype Testing**
For the testing of our prototype, we conducted both virtual and physical testing. Testing was very important to us as it helps to valdiate our solution.

<p align="center">
  <img width="500" src='assets/5cm-6.png'>
</p>
<p align="center">
  Virtual testing for bin specification.
</p>

virtual testing allowed us to have the best specification of the bin for the target audience.

<p align="center">
  <img width="500" src='assets/5cm-3.png'>
</p>
<p align="center">
  Physical testing for pixel size.
</p>

We utilised physical prototypes to test the perfect pixel size for our LED.
The main learning point from testing was that we should find the quickest way to test the solution without spending too much resources on it.

# **User Validation**
<p align="center">
  <img width="500" src='assets/user_validation.png'>
</p>
<p align="center">
  User survey result consolidated.
</p>

For the user validation, we received majority positve reviews. This indicated that the design was a success. 

# **Conclusion**
Design Thinking Innovation course is not a technical course. It teaches us how to be creative design innovators to create solutions after a detailed analysis of a problem.
