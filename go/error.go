// 自用的错误嵌套模板
package main

import (
	"errors"
	"fmt"
)

// a -> b -> c
func a() (err error) {
	err = b()
	if err != nil {
		err = fmt.Errorf("a error: %w", err)
		return
	}
	return
}

func b() (err error) {
	err = c()
	if err != nil {
		err = fmt.Errorf("b error: %w", err)
		return
	}
	return
}

func c() (err error) {
	return errors.New("c error")
}

func main() {
	err := a()
	if err != nil {
		fmt.Println(err)
		fmt.Println(errors.Unwrap(err))
		fmt.Println(errors.Unwrap(errors.Unwrap(err)))
	}
}
