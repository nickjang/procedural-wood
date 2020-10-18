# Procedural Wood Texture

It can difficult to know what the features of the wood will look like before cutting into it.
This application creates a 3D texture from a picture of wood and allows the user to cut preset shapes from it.
This project tried to estimate the contents of wood and be helpful to woodworkers or even 3D artists.

This application was written using C++ and OpenGL.

## Table of contents

- [Demo](#demo)
- [Future Work](#future-work)
- [References](#references)
- [Acknowledgments](#acknowledgments)

## Demo

<img src="./images/procedural-wood-texture.gif" align="middle" alt="A live demo of  an input image and a 3D texture generated from the image, bowl cut from the texture, or spoon cut from the texture." width="575">

A demo showing the input image and the 3D texture generated from the image (cube), bowl cut from the texture, or spoon cut from the texture.

## Future Work

Various features make up a piece of wood. Pores, rays, and grain all have different properties. 
Rings form in unique ways, depending on seasons, environmental conditions, and likely more factors. 
Real wood and it's features also differ in shading.
This program assumes the tree grows perfectly upward and applies one shader to the entire 3D texture.

## References

This project relied heavily on [research](https://research.cs.cornell.edu/wood/simulating_the_structure_and_texture_of_solid_wood.pdf) in computer graphics done by students at Cornell University.

## Acknowledgments

Thank you to the University of Pennsylvania's [Digital Media Design](http://cg.cis.upenn.edu/dmd.html) program and faculty, who helped in the completion of this project.
