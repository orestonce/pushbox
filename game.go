package pushbox

import (
	_ "embed"
	"encoding/json"
)

var gGame *PushBoxMap

//go:embed map.dat
var mapBytes []byte
var mapList []PushBoxMap

func init() {
	err := json.Unmarshal(mapBytes, &mapList)
	if err != nil {
		panic(err)
	}
	Go2Cpp_SetStage(1)
}

func Go2Cpp_SetStage(idx int) {
	if idx <= 0 || idx > len(mapList) {
		idx = 1
	}
	data, _ := json.Marshal(&mapList[idx-1])
	gGame = &PushBoxMap{}
	_ = json.Unmarshal(data, gGame)
}

func Go2Cpp_GetDataForQt() PushBoxMap {
	return *gGame
}

func Go2Cpp_DoAction(a string) bool {
	return gGame.DoAction(a)
}

func Go2Cpp_GetIsGamePass() bool {
	return gGame.IsGamePass()
}

func Go2Cpp_GetStageMax() int {
	return len(mapList)
}
