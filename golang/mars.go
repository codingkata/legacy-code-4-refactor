package main

import (
	"./mars"
)

func main() {

	travel := mars.MarsExplore{}

	travel.MakeMarsSize(5, 5)

	position := mars.Position{}
	position.X = 1
	position.Y = 2
	position.Direction = "N"

	travel.DeployCar(position)
	travel.SendCmd("LMLMLMLMM")

	positionNew := mars.Position{}
	positionNew.X = 3
	positionNew.Y = 3
	positionNew.Direction = "E"

	travel.DeployCar(positionNew)
	travel.SendCmd("MMM")

}
