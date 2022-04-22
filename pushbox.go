package pushbox

import (
	"encoding/json"
)

// 序列化、反序列化

type PushBoxMap struct {
	Stage      int     `json:",omitempty"`
	MapMaxY    int     `json:",omitempty"`
	MapMaxX    int     `json:",omitempty"`
	LastAction string  `json:",omitempty"`
	Tree       []Point `json:",omitempty"`
	Box        []Point `json:",omitempty"`
	Goal       []Point `json:",omitempty"`
	Boy        Point   `json:",omitempty"`
}

type Point struct {
	X int
	Y int
}

// 玩家操作
const (
	Up    = `U`
	Down  = `D`
	Left  = `L`
	Right = `R`
)

func (this *PushBoxMap) ToString() string {
	data, err := json.Marshal(this)
	if err != nil {
		panic(err)
	}
	return string(data)
}

func ParseMap(s string) (m *PushBoxMap) {
	m = &PushBoxMap{}
	var err error
	err = json.Unmarshal([]byte(s), m)
	if err != nil {
		return nil
	}
	if m.MapMaxY <= 0 || m.MapMaxX <= 0 {
		return nil
	}
	// 箱子数量>0
	if len(m.Box) == 0 {
		return nil
	}
	// 箱子数量和目的地数量相等
	if len(m.Goal) != len(m.Box) {
		return nil
	}
	return m
}

func (this *PushBoxMap) DoAction(action string) bool {
	this.LastAction = action
	var dy, dx int
	switch action {
	case Up:
		dy = -1
	case Down:
		dy = 1
	case Left:
		dx = -1
	case Right:
		dx = 1
	default:
		return false
	}
	x, y := this.Boy.X, this.Boy.Y
	if !this.isValidPoint(y+dy, x+dx) || findInSlice(this.Tree, y+dy, x+dx) >= 0 {
		return false
	}
	boxIdx := findInSlice(this.Box, y+dy, x+dx)
	if boxIdx >= 0 { // 下一步是箱子
		if !this.isValidPoint(y+2*dy, x+2*dx) { // 再下一步不合法
			return false
		}
		if findInSlice(this.Box, y+2*dy, x+2*dx) >= 0 || findInSlice(this.Tree, y+2*dy, x+2*dx) >= 0 { // 再下一步是箱子、树
			return false
		}
		// 更新下一步的状态
		this.Box[boxIdx].Y = y + 2*dy
		this.Box[boxIdx].X = x + 2*dx
	}
	// 更新人的状态
	this.Boy.Y += dy
	this.Boy.X += dx
	return true
}

func (this *PushBoxMap) IsGamePass() bool {
	for _, one := range this.Goal {
		if findInSlice(this.Box, one.Y, one.X) < 0 {
			return false
		}
	}
	return true
}

func (this *PushBoxMap) isValidPoint(y int, x int) bool {
	return 0 <= y && y < this.MapMaxY && 0 <= x && x < this.MapMaxX
}

func findInSlice(pointSlice []Point, y, x int) int {
	for idx, one := range pointSlice {
		if one.Y == y && one.X == x {
			return idx
		}
	}
	return -1
}
