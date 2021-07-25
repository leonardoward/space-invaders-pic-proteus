# space-invaders-pic-proteus
PG-7233 C for Embedded Systems - Project 

This project is a cover of the classic videogame Space Invaders, developed for a PIC microcontroller using [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide) and simulated on [Proteus](https://www.labcenter.com/simulation/)

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126903327-ac1e11a1-48b3-4996-8c43-2b72ceaed79f.gif">
</p>

## Table of Contents

1. [Getting Started](#getting-started) 
    1. [Source](#source)
    2. [Dependencies](#dependencies)
    3. [Building](#building)
    4. [Setup](#building)
2. [Technical Details](#technical-details) 
3. [Gameplay](#gameplay)
4. [Further Reading](#further-reading)
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

![image](https://user-images.githubusercontent.com/28768293/126903758-0a11274c-aba8-4513-a006-905f81e4ee40.png)


**[Back to top](#table-of-contents)**

## Setup

In order to run the simulation in Proteus, the user has to insert the .hex file path in the PIC preferences.

![image](https://user-images.githubusercontent.com/28768293/126903713-456fe6f5-4ce0-4bc2-a401-e80e21da7085.png)

**[Back to top](#table-of-contents)**

# Technical Details

## PIC
This project was developed on the PIC24FJ128GA010. 

## Screen
The screen used was a T6963C with 240 x 120 pixels. To manage the screen in this project enhancements were made to the library [T6963C_PIC](https://github.com/camilstaps/T6963C_PIC.git) of camilstaps


<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126905369-75503a3a-0a69-4f04-ac8c-9b231f6e1db0.gif">
</p>




## Gameplay

In the following video you can see the gameplay of this Space Invaders cover in Proteus Simulation.
At the beginning the landing page is shown, then the user can use the buttons to play the game. 

https://user-images.githubusercontent.com/28768293/126901666-feb15a27-f83b-4b7f-9aa5-6ce4ac7daadf.mp4


**[Back to top](#table-of-contents)**

# Further Reading

The folder [Documents](https://github.com/leonardoward/Sensor-Based-Ambient-Lights/tree/main/Documents) contains a Report with the design process, and a document with the Bill od Materials.

**[Back to top](#table-of-contents)**

# Authors

* **[Leonardo Ward](https://github.com/leonardoward)**
* **[Mauricio Marcano](https://github.com/rinripper)**


**[Back to top](#table-of-contents)**
