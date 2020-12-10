package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
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

func min(x int, y int, z int) int {
	if x < y && x < z {
		return x
	} else if y < z {
		return y
	} else {
		return z
	}
}

func getSmallestPerimeter(h int, w int, l int) int {
	var min int
	var min2 int

	if h <= w && h <= l {
		min = h
		if w <= l {
			min2 = w
		} else {
			min2 = l
		}
	} else if w <= h && w <= l {
		min = w
		if h <= l {
			min2 = h
		} else {
			min2 = l
		}
	} else {
		min = l
		if w <= h {
			min2 = w
		} else {
			min2 = h
		}
	}

	return min + min2
}

func getSquareFootage(h int, w int, l int) int {
	i := 2*l*w + 2*w*h + 2*h*l
	j := min(l*w, w*h, h*l)
	return i + j
}

func getRibbonLength(h int, w int, l int) int {
	i := h * w * l
	j := 2 * getSmallestPerimeter(h, w, l)
	fmt.Printf("\tH: %3d W: %3d L: %3d\t", h, w, l)
	fmt.Printf("\t%5d+%5d\n", i, j)
	return i + j
}

func parseLine(line string) (int, int, int) {
	data := strings.Split(string(line), "x")
	var newData [3]int
	for i := range data {
		newData[i], _ = strconv.Atoi(data[i])
	}
	return newData[0], newData[1], newData[2]
}

func main() {
	args := os.Args[1:]

	if len(args) != 1 {
		fmt.Printf("Usage: ./main <input>")
	}

	lines := readLines(args[0])
	var wrappingPaper int = 0
	var ribbon int = 0
	for i := range lines {
		wrappingPaper += getSquareFootage(parseLine(lines[i]))
		ribbon += getRibbonLength(parseLine(lines[i]))
		fmt.Printf("Present #%d\n\tSquare Footage: %d\n\tRibbon Length: %d\n\n",
			i,
			getSquareFootage(parseLine(lines[i])),
			getRibbonLength(parseLine(lines[i])))
	}
	fmt.Printf("Sum of Square Footage: %d\n", wrappingPaper)
	fmt.Printf("Sum of Ribbon Length:  %d\n", ribbon)
}
