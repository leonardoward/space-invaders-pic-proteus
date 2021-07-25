# space-invaders-pic-proteus
PG-7233 C for Embedded Systems - Project 

This project is a cover of the classic videogame Space Invaders, developed for a PIC microcontroller using [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide) and simulated on [Proteus](https://www.labcenter.com/simulation/)

<p align="center">
  <img width="460" height="300" src="https://user-images.githubusercontent.com/28768293/126903327-ac1e11a1-48b3-4996-8c43-2b72ceaed79f.gif">
</p>




This project contains the firmware and simulation of videogame . 

The microprocessor used was the PIC24FJ128GA010 to manage all the digital signals. This repository includes a [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide) project, with the source code for the microcontroller (the folder Hela.X). It also contains a [Proteus](https://www.labcenter.com/simulation/) project  used to simulate and test the electronic design.

The design is a modular system that allows the user to multiple usage modes for an [110V/220V LED Strip](https://es.aliexpress.com/item/1005001989354694.html?spm=a2g0o.productlist.0.0.15731814f4HM3v&algo_pvid=82597dfd-2696-4544-87ad-ca4784616c1c&algo_expid=82597dfd-2696-): they can be turn on/of manually or automatically depending on a the time of the day or the amount of light in the environment.

For further information about the design requirements and the overall design visit the [Documents](https://github.com/leonardoward/Sensor-Based-Ambient-Lights/tree/main/Documents) folder for a more detailed report.

## Table of Contents

1. [About the Project](#about-the-project)
2. [Getting Started](#getting-started)
    1. [Dependencies](#dependencies)
    2. [Building](#building)
    3. [Getting the Source](#getting-the-source)
3. [Gameplay](#gameplay)
4. [Further Reading](#further-reading)
5. [Authors](#authors)

# About the Project

The following image presents the Proteus Project with the complete electronic design:

![Proteus Project](./images/proteus_schematic.png)

The following video presents the available features achieved with the last version of the source code.

[![Demonstration](./images/demonstration.jpeg)](https://youtu.be/3KqcJgEQBLA "Demostración Proyecto 2 HELA - Luces inteligentes")

# Getting Started

## Dependencies

The project only requires the following development environments:

* [MPLABX](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide)
* [Proteus](https://www.labcenter.com/simulation/)

The Proteus project uses components the are contained in the environment by default, doesn't require additional component imports.

**[Back to top](#table-of-contents)**

## Building

The building process is performed in the MPLABX development environment.

**[Back to top](#table-of-contents)**

## Getting the Source

This project is [hosted on GitHub](https://github.com/leonardoward/space-invaders-pic-proteus/). You can clone this project directly using this command:

```
git clone https://github.com/leonardoward/space-invaders-pic-proteus.git
```

**[Back to top](#table-of-contents)**

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
