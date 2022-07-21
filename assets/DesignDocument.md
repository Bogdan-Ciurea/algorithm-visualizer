# Design Document

This file is responsible for better explaining the Low Level Design of this project and how the project works

## Table of Contents

 1. [Overview](#overview)
 2. [Utils.h](#utils.h)
 3. [Node Class](#node-class)
 4. [Edge Class](#edge-class)
 5. [Pillar class](#pillar-class)
 6. [Other Functions](#other-functions)
 7. [Graph class](#fraph-class)
 8. [Trees class](#trees-class)
 9. [Sorter class](#sorter-class)
 10. [Search class](#search-class)
 11. [Interface class](#interface-class) 

## Overview

![Diagram of the structure of this project](diagram.jpg)

As explanted before this project is going to use Raylib 4.0.0 and RayGui 3.1. Headers that will import these libraries are going to be located in the `/include` folder.

The main components of this project are:

 - The main function, that will create an Interface object
 - The Interface object which will take care of:
	 - drawing the main menu to the screen
	 - receiving the information from the user. This will decide which type of algorithm object (graph, trees etc.) to build and launch
 - The Graph Structure will contain 3 Classes (Node, Edge, Graph) and more functions for animation. This Structure will take care of displaying the unique header and processing the information from the user
 - The Trees, Sorting and Search Structures have the same description the the Graph Structure one

## Utils.h
This file will be responsible for defining all the Colors that we are going to use in the project, all the enumerators and the libraries.

## Node Class

## Edge Class

## Pillar Class

## Other Functions

## Graph Class

## Trees Class

## Sorter Class

## Search Class

## Interface Class
