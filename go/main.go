// 注释
// 变量
// 函数
// 流程控制 - if for switch
// 面向对象 - struct + method
// 泛型 - 无
// 反射 - import reflect
// 模块 - package
// 文档 - go doc 'os' 或 godoc 'os'

// 基本数据结构: 列表, 字典
// 并发

// 定义模块
package main

// 使用模块
import (
	"fmt"
)

// 变量定义
// type 可忽略, go 会自动推导类型
var g_globalVar int = 10

const g_constVar uint = 100

// 函数定义
func funcName(param0 int, param1 int) (ret0 int, ret1 int) {
	return ret0, ret1
}

// 函数可选参数
// 无法原生实现命名参数, 只能使用可选参数+结构体来时间, 如下
// func Function(arg0 int,  params Params, args ...interface{})
func funcArgs(args ...interface{}) {
	if len(args) <= 0 {
		return
	}
	funcArgs(args[:len(args)-1]...)
}

// 类以及方法
type Rect struct {
	width  uint
	height uint
}

func (self Rect) area() uint {
	return self.width * self.height
}

type Man struct {
	name string
}

type Woman struct {
	name string
}

func (self *Man) SayHi() {
	fmt.Println("I am a man")
}

func (self *Woman) SayHi() {
	fmt.Println("I am a woman")
}

type Human interface {
	SayHi()
}

// 并发
func gofunc(c, quit chan int) {
	for {
		select {
		case x := <-c:
			fmt.Println("receive", x)
		case <-quit:
			fmt.Println("quit")
			break
		}
	}
}

// 反射
func printType(v interface{}) {
	switch value := v.(type) {
	case int:
		fmt.Println("type of param is int", value)
	default:
		fmt.Println("unknown type", value)
	}
}

func main() {
	fmt.Printf("Hello, world\n")
	fmt.Printf("%v, %v\n", g_globalVar, g_constVar)

	// 数组和列表(切片), slice 方法 len, append, cap, copy
	array := [...]int{1, 2, 3}
	slice := []int{3, 2, 1}
	// 字典
	// dict := make(map[string]int)
	// dict["a"] = 1
	dict := map[string]int{
		"a": 1,
		"b": 2,
		"c": 3,
	}

	fmt.Printf("%v\n", array)
	fmt.Printf("%v\n", slice)
	fmt.Printf("%v\n", dict)
	fmt.Println(dict)

	box := Rect{
		width:  3,
		height: 4,
	}
	fmt.Println("area of rectangle is", box.area())

	// 动态绑定(多态)
	var human Human
	man := Man{"man"}
	woman := Woman{"woman"}
	human = &man
	human.SayHi()
	human = &woman
	human.SayHi()

	c := make(chan int)
	quit := make(chan int)
	go gofunc(c, quit)
	c <- 1
	c <- 2
	quit <- 3

	printType(3)
	printType(3.0)
}
