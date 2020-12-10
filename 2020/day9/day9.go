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

func shiftDown(data []int, lines []string, curIndex int) []int {
	for i := 0; i < len(data); i++ {
		data[i], _ = strconv.Atoi(lines[curIndex+i])
	}

	return data
}

func checkIfTrue(data []int, sum int) bool {
	for i := 0; i < len(data); i++ {
		for j := i + 1; j < len(data); j++ {
			//		fmt.Printf("(%d,%d)->%d+%d=%d\n", i, j, data[i], data[j], data[i]+data[j])
			if data[i]+data[j] == sum {
				return true
			}
		}
	}
	return false
}

func gatherWeakness(data []int, sum int, index int, length int) bool {
	//fmt.Printf("Starting: %d\tLength%d\t", index, length)
	checkSum := 0
	for i := index; i <= length; i++ {
		//fmt.Printf("%d\t", data[i])
		checkSum += data[i]
	}
	//   9fmt.Printf("\n")
	return checkSum == sum
}

func main() {
	args := os.Args[1:]

	if len(args) != 2 {
		fmt.Printf("Usage: ./main <input> <preamble length>\n")
		os.Exit(1)
	}

	lines := readLines(args[0])
	preamble, _ := strconv.Atoi(args[1])

	fmt.Printf("Preamble Length: %d\n", preamble)
	fmt.Printf("%v\n", lines)

	data := make([]int, preamble, preamble)

	for i := 0; i < preamble; i++ {
		data[i], _ = strconv.Atoi(lines[i])
	}
	curIndex := 0
	weakness := 0
	shiftDown(data, lines, curIndex)
	fmt.Printf("%d->%v\n", len(data), data)

	for curIndex+preamble < len(lines)-1 {
		weakness, _ = strconv.Atoi(lines[curIndex+preamble])
		//fmt.Printf("%d\n", f)
		check := checkIfTrue(data, weakness)
		if check == false {
			fmt.Printf("%v\n", data)
			fmt.Printf("Value: %d\n", weakness)
			break
		}
		curIndex += 1
		shiftDown(data, lines, curIndex)
		//fmt.Printf("%d->%v\n", len(data), data)
	}

	fmt.Printf("Weakness: %d\tIndex: %d\n", weakness, curIndex)
	data = make([]int, len(lines), len(lines))

	for i := 0; i < len(lines); i++ {
		data[i], _ = strconv.Atoi(lines[i])
	}

	start_i := 0
	end_i := 0
	for i := 0; i < curIndex; i++ {
		for j := 2; j < curIndex; j++ {
			if gatherWeakness(data, weakness, i, j) {
				start_i = i
				end_i = j
			}
		}
	}
	fmt.Printf("%d through %d\n", start_i, end_i)
	for i := start_i; i <= end_i; i++ {
		fmt.Printf("%d\n", data[i])
	}
}
