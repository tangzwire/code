// Stefan Nilsson 2013-03-13

// This program implements an ELIZA-like oracle (en.wikipedia.org/wiki/ELIZA).
package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strings"
	"time"
	"regexp"
)

const (
	star   = "Pythia"
	venue  = "Delphi"
	prompt = "> "
	numberofquestions = 15 //Number of questions that can be answered by Pythia at a time.
)

func main() {
	fmt.Printf("Welcome to %s, the oracle at %s.\n", star, venue)
	fmt.Println("Your questions will be answered in due time.")

	oracle := Oracle()
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print(prompt)
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		fmt.Printf("%s heard: %s\n", star, line)
		oracle <- line // The channel doesn't block.
	}
}

// Oracle returns a channel on which you can send your questions to the oracle.
// You may send as many questions as you like on this channel, it never blocks.
// The answers arrive on stdout, but only when the oracle so decides.
// The oracle also prints sporadic prophecies to stdout even without being asked.
func Oracle() chan<- string {
	questions := make(chan string, numberofquestions)
	prophecies := make(chan string, numberofquestions)

	go MakeProphecies(questions, prophecies)
	go PrintAnswers(prophecies)

	return questions
}

//Prints all the answers for every question that is sent.
//Uses a delay to pause before answering the question.
func PrintAnswers(answers <-chan string) {
	for answer := range answers {
		fmt.Print("\r")
		for _, char := range answer {
			time.Sleep(time.Duration(20+rand.Intn(10)) * time.Millisecond)
			fmt.Print(string(char))
		}
		fmt.Print("\n", prompt)
	}
}

//Make answers to the questions, and also predictions (with delay).
//If there is no question, make  non-sense predictions (with delay).
func MakeProphecies(questions chan string, prophecies chan string){
	for {
		time.Sleep(time.Duration(10+rand.Intn(5)) * time.Second)
		select {
		case question := <-questions:
			MakeProphecy(question, prophecies)
		default:
			MakeProphecy("", prophecies)
		}
	}
}

//If there is no question, make non-sense predictions (loneliness).
//If there is a question, answer it.
func MakeProphecy(question string, prophecies chan<- string) {

	if question == "" {
		loneliness := []string{
			"You know what I like? I like oranges.",
			"If I install Windows 7 32 bit two times, will I be able to play a game that requires Windows 7 64 bit?",
			"Let me find out what the hell is going on under my pillow....",
			"An apple a day makes the pears go away!",
			"Abstraction is not all that great!",
			"The sky is not yet ready to die.",
		}
		prophecies <- "...\nHello? Is somebody here? :-O \n" + loneliness[rand.Intn(len(loneliness))]
	} else {
		prophecy(question, prophecies)
	}
}

// This is the oracle's secret algorithm.
// It waits for a while and then sends a message on the answer channel.
func prophecy(question string, answer chan<- string) {

	//If the questioner is being disrespectful, a negative answer will be issued.
	//Uses regex to find some negative words in a question.
	disrespectful, _ := regexp.MatchString("(?i)(idiot|you|stupid|moron|punkass)", question)
	if disrespectful {
		answer <- "Okey, now you are not showing any respect! Security, come and get this piece of crap out of here!"
		return
	}

	//If the questioner is being respectful, a positive answer will be issued.
	//Uses regex to find some positive words in a question.
	respectful, _ := regexp.MatchString("(?i)help", question)
	properAddress, _ := regexp.MatchString("(?i)("+star+"|king|sir|master|officer|professor|best)", question)
	respectful = respectful && properAddress
	if !respectful {
		answer <- "That is right, you are showing respect to the Oracle! Good."
		return
	}
	// Find the longest word.
	longestWord := ""
	words := strings.Fields(question) // Fields extracts the words into a slice.
	for _, w := range words {
		if len(w) > len(longestWord) {
			longestWord = w
		}
	}

	// Cook up some pointless nonsense.
	nonsense := []string{
		"The moon is dark.",
		"The sun is bright.",
		"Look up and get lost",
		"A cat and a house, instead of a hat and a mouse.",
		"Why ruin a relationship when you can ruin a relationboat?",
		"If the earth is round, then what is TV?",
	}
	answer <- nonsense[rand.Intn(len(nonsense))]
}

func init() { // Functions called "init" are executed before the main function.
	// Use new pseudo random numbers every time.
	rand.Seed(time.Now().Unix())
}
