package pushbox

import (
	"testing"
)

func TestParseMap(t *testing.T) {
	m := ParseMap("[3,2]012345")
	if m == nil {
		t.Fatal("m == nil")
		return
	}
	str := m.ToString()
	if str != "[3,2]\n01\n23\n45\n" {
		t.Fatal(str)
		return
	}
	m = ParseMap("x")
	if m != nil {
		t.Fatal("m != nil")
	}
}
