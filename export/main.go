package main

import (
	"github.com/orestonce/go2cpp"
	"github.com/orestonce/pushbox"
)

func main() {
	ctx := go2cpp.NewGo2cppContext(go2cpp.NewGo2cppContext_Req{
		CppBaseName:                 "pbcore",
		EnableQtClass_RunOnUiThread: false,
	})
	ctx.Generate1(pushbox.Go2Cpp_GetStageMax)
	ctx.Generate1(pushbox.Go2Cpp_SetStage)
	ctx.Generate1(pushbox.Go2Cpp_GetDataForQt)
	ctx.Generate1(pushbox.Go2Cpp_DoAction)
	ctx.Generate1(pushbox.Go2Cpp_GetIsGamePass)
	ctx.MustCreateAmd64LibraryInDir("pushbox-qt")
}
