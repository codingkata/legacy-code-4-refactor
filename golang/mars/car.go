package mars

import (
	"errors"
	"github.com/google/uuid"
)

type CarMove interface {
}

type Car struct {
	id              string
	StartPosition   Position
	CurrentPosition Position
	MoveList        []string
}

func CreateCar(position Position) *Car {
	car := &Car{}
	car.StartPosition = position
	car.CurrentPosition = position
	car.id = uuid.New().String()
	return car
}

func (c *Car) RunCmd(cmd string) (Position, error) {
	var err error
	switch cmd {
	case "L":
		_, err = c.TurnLeft()
		break
	case "R":
		_, err = c.TurnRight()
		break
	case "M":
		_, err = c.Move()
		break
	default:
		err = errors.New("错误的命令")
	}
	return c.CurrentPosition, err
}

func (c *Car) TurnLeft() (Position, error) {
	var err error = nil
	switch c.CurrentPosition.Direction {
	case NORTH:
		c.CurrentPosition.Direction = WEST
		break
	case WEST:
		c.CurrentPosition.Direction = SOUTH
		break
	case SOUTH:
		c.CurrentPosition.Direction = EAST
		break
	case EAST:
		c.CurrentPosition.Direction = NORTH
		break
	default:
		err = errors.New("未知的车辆方向")
	}
	return c.CurrentPosition, err
}

func (c *Car) TurnRight() (Position, error) {
	var err error = nil
	switch c.CurrentPosition.Direction {
	case NORTH:
		c.CurrentPosition.Direction = EAST
		break
	case WEST:
		c.CurrentPosition.Direction = NORTH
		break

	case SOUTH:
		c.CurrentPosition.Direction = WEST
		break
	case EAST:
		c.CurrentPosition.Direction = SOUTH
		break
	default:
		err = errors.New("未知的车辆方向")
	}
	return c.CurrentPosition, err
}

func (c *Car) Move() (Position, error) {
	var err error = nil
	switch c.CurrentPosition.Direction {
	case "N":
		c.CurrentPosition.Y += 1
		break
	case "W":
		c.CurrentPosition.X -= 1
		break

	case "S":
		c.CurrentPosition.Y -= 1
		break
	case "E":
		c.CurrentPosition.X += 1
		break
	default:
		err = errors.New("未知的车辆方向")
	}
	return c.CurrentPosition, err
}
