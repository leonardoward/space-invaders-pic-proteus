# space-invaders-pic-proteus
PG-7233 C for Embedded Systems - Project

This project is a cover of the classic videogame Space Invaders, developed for a PIC microcontroller using [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide) and simulated on [Proteus](https://www.labcenter.com/simulation/)

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126903327-ac1e11a1-48b3-4996-8c43-2b72ceaed79f.gif">
</p>

<p align="center">
  <small> (video with increased speed) </small>  
</p>


## Table of Contents

1. [Getting Started](#getting-started)
    1. [Source](#source)
    2. [Dependencies](#dependencies)
    3. [Building](#building)
    4. [Setup](#building)
2. [Technical Details](#technical-details)
3. [Simulation](#simulation)
4. [Upcoming Enhancements](#upcoming-enhancements)
5. [Authors](#authors)


# Getting Started

## Source

This project is [hosted on GitHub](https://github.com/leonardoward/space-invaders-pic-proteus/). You can clone this project directly using this command:

```
git clone https://github.com/leonardoward/space-invaders-pic-proteus.git
```

**[Back to top](#table-of-contents)**

## Dependencies

The project only requires the following development environments:

* [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide)
* [Proteus](https://www.labcenter.com/simulation/)

The Proteus project uses components the are contained in the environment by default, doesn't require additional component imports.

**[Back to top](#table-of-contents)**

## Building

The building process is performed in the MPLAB development environment to generate the .hex file necessary for the Proteus Simulation. This is done by clicking the clean and build button in MPLAB

<p align="center">
  <img src="https://user-images.githubusercontent.com/28768293/126903758-0a11274c-aba8-4513-a006-905f81e4ee40.png">
</p>

**[Back to top](#table-of-contents)**

## Setup

In order to run the simulation in Proteus, the user has to insert the .hex file path in the PIC preferences.

<p align="center">
  <img src="https://user-images.githubusercontent.com/28768293/126903713-456fe6f5-4ce0-4bc2-a401-e80e21da7085.png">
</p>

**[Back to top](#table-of-contents)**

# Technical Details

## PIC
This project was developed on the [PIC24FJ128GA010](https://ww1.microchip.com/downloads/en/DeviceDoc/39747F.pdf).

## Screen
The LCD controller used was a T6963C to drive a screen of 240 x 128 pixels. In this project enhancements were made to the library [T6963C_PIC](https://github.com/camilstaps/T6963C_PIC.git) of camilstaps in order to drive the screen.


<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126905598-59ec5fc8-99f4-45c6-aaa4-136d161fb627.gif">
</p>

<p align="center">
  <small> (video with increased speed) </small>  
</p>

## Buttons
The buttons used were three push buttons native of proteus in pull-up configuration, two of them for lateral movement and the other one to shoot.


<p align="center">
  <img src="https://user-images.githubusercontent.com/28768293/126905713-e26a1e39-a2d3-4375-ba1e-27bcb0c8c7eb.png">
</p>

## Two Way Render  
The way the invaders render is variable: When the invaders move from right to left the rendering direction is from left to right, and vice versa. This mechanism allows collision detection to be performed on the outermost invader only once at the beginning of the update cycle, regardless of the number of live invaders.   

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126906704-42b87f3c-6dd1-4e53-9428-c085668457ec.gif">
</p>

<p align="center">
  <small> (video with increased speed) </small>  
</p>

## Custom Made Sprite
In order to draw in the screen with the T6963C symbol generator, custom 8x8 sprite were made for each character in the game. The three types of invaders sprites were implemented with their respective four animations: i) position 'a', ii)position 'b', iii)position 'a' dodging laser shot, iv) position 'b' dodging laser shot; the spaceship and mothership sprites, the barriers sprites with the ability to be destroyed with 3 hits, laser shots and explotion sprites.


<p align="center">
  <img src="https://user-images.githubusercontent.com/28768293/126910085-ce707ba6-35f9-4abf-8a65-37cb2ffe1561.png">
</p>

The tool used to draw and export the images was [Piskel](https://www.piskelapp.com/), and the tool used to generate de arrays file from the bitmap pictures was [LCD Assistant](http://en.radzio.dxp.pl/bitmap_converter/)


<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126908755-41d00411-8793-40db-b4b7-224eb8be5ca1.gif">
</p>

<p align="center">
  <small> (video with increased speed) </small>  
</p>


## Game Logic
Attack intelligence for invaders has been implemented to spice up the gameplay. Also collision detector alien/barrier and collision detector alien/spaceship, live and score systems, and game over/restart screen were implemented.

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126909046-c2f73823-012a-4933-a722-3ef9540c58d5.gif">
</p>

<p align="center">
  <small> (video with increased speed) </small>  
</p>

## Game Architecture

We implemented the game using 4 basic design patterns:

- [Game loop](https://gafferongames.com/post/fix_your_timestep/): the main loop contains an inner loop that manages the inputs, the update of each component and the rendering of each component. The objective of this pattern (process input -> update -> render) is to decouple the progression of the game from user input and processor speed. We managed to decouple it from the user input but not the processor speed, right now it will run at maximum speed.

- Update Method: each game component has an update method that is used to process on frame at a time.

- Component: each game object (spaceship, invader, mothership, bullet and barrier) is a single entity that can be spanned over multiple domains(locations) without coupling the domains to each other. We also use the Prototype pattern, we can create different versions of the game object by creating different instances of the same structure.

- State: each component has a state, and it is often used to define if the type of animation has to change or if it should be removed from the game.

The following image presents a Flowchart of the game.    

<p align="center">
  <img src="./pictures/game_architecture.jpg">
</p>

We implemented different structures to solve different specific problems that arrive during development, we will describe a little bit more about them in the following sections.

### Animation of a Single Game Object

We are using [Singly Linked Circular Lists](https://en.wikipedia.org/wiki/Linked_list) to manage the animations of the game objects. We only required one or two sprites, but the list is also very convenient during the rendering phase.

<p align="center">
  <img src="./pictures/animation_list.jpg">
</p>

### Animation of a Group of Invaders

The invaders have a different rendering order depending of the direction in which the group is moving:

<p align="center">
  <img src="./pictures/alien_list.jpg">
</p>

- If the group is moving from left to right, it will render the invader from right to left depending on its position in the group. From "Tail Vertical" to "Head Vertical" in the image.

- If the group is moving from right to left, it will render the invader from left to right depending on its position in the group. From "Head Vertical" to "Tail Vertical" in the image.

- If the group is moving from top to bottom, it will render the invader from bottom to top depending on its position in the group. From "Head Horizontal" to "Tail Horizontal" in the image.

### Game Map

To detect the collisions between game objects we created a game map, a 2D array with the size of the screen where each element contains a pointer to the game object that is associated to that X Y position. This map is updated with each frame according to the new positions of the objects.   

<p align="center">
  <img src="./pictures/game_map.jpg">
</p>

## Simulation

In the following video you can see the gameplay of this Space Invaders cover in Proteus Simulation.
At the beginning the landing page is shown, then the user can use the buttons to play the game.

https://user-images.githubusercontent.com/28768293/126901666-feb15a27-f83b-4b7f-9aa5-6ce4ac7daadf.mp4


**[Back to top](#table-of-contents)**

# Upcoming Enhancements

Integrate audio to gameplay, this was tried without success in another project (mplab_audio) using the "output comparator interruptions" of the PIC to generate a PWM signal that later in Proteus is filtered to get the sound. The main problem encountered was the delay of the Proteus Simulation.

The sounds used were from the original game released in 1978 by Taito (available [here](https://www.classicgaming.cc/classics/space-invaders/sounds)), and converted to array with the tool [WAVToCode](https://colinjs.com/software.html) by Colin Seymour


https://user-images.githubusercontent.com/28768293/126909726-e98398e2-245a-4c26-a3c1-7c32b6fe126c.mp4



**[Back to top](#table-of-contents)**

# Authors

* **[Leonardo Ward](https://github.com/leonardoward)**
* **[Mauricio Marcano](https://github.com/rinripper)**


**[Back to top](#table-of-contents)**
