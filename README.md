# Abaqus-simulator

This project aims at creating a program which supports the graphics interface and the communications between the GUI and a remote system (server). These processes may communicate by signals but need to use one or more shared memories to exchange information.
In this case, it was developed a monitoring system from a finite element program Abaqus. This monitoring is performed through a graphic interface (GTK). However
this application only lets you perform a predefined beam loading test and only changing it's length, Young module and Poisson Coefficient.


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Things you need to install if you already haven't:

```
Abaqus 6.14
GTK+
```


### Installing

A step by step series of examples that tell you have to get a development env running

First you need to [install](https://github.com/Solid-Mechanics/Install-ABAQUS-on-Ubuntu) the Abaqus Finite Element Analysis software on your linux machine.

Then, install GTK+ :

```
sudo apt-get install libgtk-3-dev
```

After Installing GTK+ and Abaqus, run the following commands:

```
mkdir build
cd build
cmake ..
make
./server <port number>
./Gtkgui <port number>
```


### Examples

![test](https://i.imgur.com/z5aP8wA.png)

![test](https://i.imgur.com/EhgbFBk.png)

![test](https://i.imgur.com/v08BXHi.png)



## Authors

* **Miguel Gaspar** - *Initial work* - [Repository](https://github.com/miguelggaspar)

See also the list of [contributors](https://github.com/miguelggaspar/Abaqus-simulator/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
