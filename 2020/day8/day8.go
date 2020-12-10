package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type instruction struct {
	instruction string
	argument    int
	visited     bool
}

func readLines(file string) ([]string, error) {
	f, err := os.Open(file)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	var lines []string
	scanner := bufio.NewScanner(f)

	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines, scanner.Err()
}

func parseLine(line string) instruction {
	instructions := strings.Split(string(line), " ")
	var i instruction

	i.instruction = instructions[0]
	i.argument, _ = strconv.Atoi(instructions[1])
	i.visited = false

	return i
}

func printInstructions(words []instruction) {
	fmt.Printf("Length of Program: %d\n", len(words))
	for i := range words {
		fmt.Printf("%4d:%4s\t%3d,%t\n", i, words[i].instruction, words[i].argument, words[i].visited)
	}
}

func runProgramOnce(words []instruction) (int, bool) {
	i := 0
	acc := 0
	marker := false

	for !words[i].visited {
		opcode := words[i].instruction
		argument := words[i].argument
		words[i].visited = true

		if opcode == "nop" {
			i += 1
		} else if opcode == "acc" {
			acc += argument
			i += 1
		} else if opcode == "jmp" {
			i += argument
		}
	}
	return acc, marker
}

func runProgram(words []instruction) (int, bool) {
	i := 0
	acc := 0
	marker := false

	for !marker {
		if i == len(words) {
			break
		}
		if words[i].visited == true {
			marker = true
			break
		}
		opcode := words[i].instruction
		argument := words[i].argument
		words[i].visited = true

		if opcode == "nop" {
			i += 1
		} else if opcode == "acc" {
			acc += argument
			i += 1
		} else if opcode == "jmp" {
			i += argument
		}
	}

	return acc, marker
}

func main() {
	args := os.Args[1:]

	if len(args) != 1 {
		fmt.Printf("Usage: ./main <input>")
	}

	lines, _ := readLines(args[0])
	var words = make([]instruction, 0, 0)

	for i := range lines {
		words = append(words, parseLine(lines[i]))
	}

	printInstructions(words)

	instructions := make([]instruction, len(words))
	copy(instructions, words)
	a, b := runProgramOnce(instructions)
	fmt.Printf("Part 1: %d\n", a)
	for i := range words {
		copy(instructions, words)

		if instructions[i].instruction == "jmp" {
			instructions[i].instruction = "nop"
		} else if instructions[i].instruction == "nop" {
			instructions[i].instruction = "jmp"
		}

		a, b = runProgram(instructions)
		if !b {
			fmt.Printf("Part 2: %d\n", a)
		}
	}
	_ = b
}
