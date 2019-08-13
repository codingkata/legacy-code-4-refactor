package mars

import (
	"github.com/sirupsen/logrus"
	"strconv"
	"strings"
)

type MarsMap struct {
	X int
	Y int
}

type MarsExplore struct {
	CarActive            *Car
	isActiveCarFinishJob bool
	CarDrop              map[string]Position
	MarsMap              MarsMap
}

func CreateTravel() *MarsExplore {
	travel := &MarsExplore{}
	travel.isActiveCarFinishJob = true
	return travel
}

func (t *MarsExplore) MakeMarsSize(x int, y int) {
	marsMap := MarsMap{}
	marsMap.X = x
	marsMap.Y = y
	t.MarsMap = marsMap
}

func (t *MarsExplore) DeployCar(position Position) bool {
	if t.CarActive != nil && !t.isActiveCarFinishJob {
		logrus.Info("current car dont finish job, could not add new car")
		return false
	}
	car := CreateCar(position)
	t.CarActive = car
	return true
}

func (t *MarsExplore) SendCmd(cmds string) error {
	var err error
	cmdArrays := strings.Split(cmds, "")
	for _, cmd := range cmdArrays {
		lastPosition := t.CarActive.CurrentPosition
		if cmd == "M" && t.isCarDropBefore(lastPosition) {
			logrus.Info("曾经有车掉下去了, 别走!")
			continue
		}
		currentPosition, err := t.CarActive.RunCmd(cmd)
		logrus.Debug("current position is", currentPosition)
		if err != nil {
			logrus.Info("", err)
			break
		}
		if t.isCarDrop() {
			t.AddCarToDrop(lastPosition)
			t.CarActive = nil
			// 车掉落之后, 不在执行命令
			break
		}
	}
	if t.CarActive != nil {
		logrus.Info(strconv.Itoa(t.CarActive.CurrentPosition.X) + " " +
			strconv.Itoa(t.CarActive.CurrentPosition.Y) + " " +
			t.CarActive.CurrentPosition.Direction)
	}
	t.isActiveCarFinishJob = true
	return err
}

func (t *MarsExplore) isCarDrop() bool {
	if t.CarActive == nil {
		return false
	}
	if t.CarActive.CurrentPosition.X > t.MarsMap.X || t.CarActive.CurrentPosition.Y > t.MarsMap.Y {
		return true
	}
	return false
}

func (t *MarsExplore) AddCarToDrop(lastPosition Position) {
	if t.CarDrop == nil {
		t.CarDrop = make(map[string]Position)
	}
	dropPosition := Position{}
	dropPosition.X = lastPosition.X
	dropPosition.Y = lastPosition.Y
	dropPosition.Direction = lastPosition.Direction
	t.CarDrop[t.CarActive.id] = dropPosition
	logrus.Info(strconv.Itoa(lastPosition.X) + " " +
		strconv.Itoa(lastPosition.Y) + " " +
		lastPosition.Direction + " RIP ")
}

func (t *MarsExplore) isCarDropBefore(currentPosition Position) bool {
	var isDropPosition = false
	if t.CarDrop == nil {
		return false
	}
	for _, dropPosition := range t.CarDrop {
		if IsPositionEquel(currentPosition, dropPosition) {
			isDropPosition = true
			break
		}
	}
	return isDropPosition
}

func IsPositionEquel(currentPosition Position, targetPosition Position) bool {
	if currentPosition.Direction == targetPosition.Direction && currentPosition.X == targetPosition.X &&
		currentPosition.Y == targetPosition.Y {
		return true
	}
	return false
}
