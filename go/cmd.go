// 自用命令行工具模板
package main

import (
	"flag"
	"fmt"
	"log/slog"
	"os"
	"path/filepath"
	"runtime"
	"time"
)

func getCurrentDir() string {
	// 获取当前目录
	_, file, _, ok := runtime.Caller(0)
	if !ok {
		panic("Failed to get current file path")
	}
	return filepath.Dir(file)
}

func initLogger() *os.File {
	fname := filepath.Join(getCurrentDir(), "stdout.log")
	f, err := os.OpenFile(fname, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		panic(err)
	}

	// 创建 JSON 格式的 handler
	logger := slog.New(slog.NewTextHandler(f, &slog.HandlerOptions{
		Level: slog.LevelDebug, // 设置日志级别
	}))

	// 设置为默认 logger
	slog.SetDefault(logger)

	slog.Info("Inited logger!")

	return f
}

func _main(args []string) int {
	fs := flag.NewFlagSet(filepath.Base(args[0]), flag.ExitOnError)
	var sleep float64
	fs.Float64Var(&sleep, "sleep", 60, "seconds to sleep")
	fs.Usage = func() {
		cmd := filepath.Base(args[0])
		fmt.Fprintf(fs.Output(), "Usage of %s:\n", cmd)
		fmt.Fprintf(fs.Output(), "  %s [OPTIONS] [ARGS ...]\n\n", cmd)

		fs.PrintDefaults()

		fmt.Fprintln(fs.Output(), "\nExamples:")
		fmt.Fprintf(fs.Output(), "  %s -help\n", cmd)
	}
	fs.Parse(args[1:])

	if len(args) <= 1 {
		fs.Usage()
		return 0
	}

	if sleep > 0 {
		time.Sleep(time.Duration(sleep * float64(time.Second)))
	}

	return 0
}

func main() {
	os.Exit(_main(os.Args))
}
