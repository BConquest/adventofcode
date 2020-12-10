package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func readLines(file string) []string {
	content, err := ioutil.ReadFile(file)
	if err != nil {
		fmt.Printf("Error Reading File: %s\n", file)
	}
	lines := strings.Split(string(content), "\n")
	return lines
}

func main() {
	args := os.Args[1:]

	if len(args) != 1 {
		fmt.Printf("Usage: ./main <input>")
	}

	lines := readLines(args[0])
}
