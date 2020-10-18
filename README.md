# Procedural Wood Texture

Create a 3D texture from a picture of wood and cut shapes from it. 

This application was written using C++ and OpenGL.

## Table of contents

- [Demo](#demo)
- [Problem and Motivation](#problem-and-motivation)
- [Future Work](#future-work)
- [References](#references)
- [Acknowledgments](#acknowledgments)

## Demo

<img src="./images/procedural-wood-texture-demo.gif" align="middle" alt="A live demo of  an input image and a 3D texture generated from the image, bowl cut from the texture, or spoon cut from the texture." width="575">

A demo showing the input image and a cube (the 3D texture generated from the image), bowl cut from the texture, or spoon cut from the texture.

## Problem and Motivation

Sometimes when working with a piece of wood it is difficult to know what the features of the wood will look like after cutting into it.
It could be helpful to estimate the inside of wood, and it might be helpful to other woodworkers or 3D artists to have a variety of 3D wood textures available.

## Future Work

Various features make up a piece of wood. Pores, rays, and grain all have different properties. 
Rings form in unique ways, depending on seasons, environmental conditions, and likely more. 
Real wood and it's features also differ in shading.
This program assumes the tree grows perfectly upward and applies one shader to the entire 3D texture.

## References

This project relied heavily on research in computer graphics done by students at Cornell University.
[Research paper](https://research.cs.cornell.edu/wood/simulating_the_structure_and_texture_of_solid_wood.pdf)

## Acknowledgments

Thank you to the University of Pennsylvania's [Digital Media Design](http://cg.cis.upenn.edu/dmd.html) program and faculty, who helped in the completion of this project.
