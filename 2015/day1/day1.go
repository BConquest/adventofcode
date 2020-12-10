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

func getDepth(data string) (int, int) {
	var depth int
	var first int = -1
	depth = 0
	for i, c := range data {
		fmt.Printf("CHAR: %4c\tDEPTH: %4d\tINDEX: %6d\n", c, depth, i)
		if c == '(' {
			depth += 1
		} else {
			depth -= 1
		}
		if depth == -1 && first == -1 {
			first = i + 1
		}
	}
	return depth, first
}

func main() {
	args := os.Args[1:]

	if len(args) != 1 {
		fmt.Printf("Usage: ./main <input>")
	}

	lines := readLines(args[0])
	fmt.Printf("%s\n", lines[0])
	i, j := getDepth(lines[0])
	fmt.Printf("Depth: %d\nFirst Basement Entrance: %d\n", i, j)
}
