package main

import (
	"fmt"
	"time"
)

func Remind(a string, delay time.Duration) {

	//Multiplicates delay with seconds.
	time.Sleep(delay * time.Second)

	var seconds int = int(delay)
	fmt.Printf("Every %d", seconds)

	//Controls the delay value and assigned the correct english numeral.
	if seconds == 1 || seconds == 21 || seconds == 31 {
		fmt.Printf("st")
	} else if seconds == 2 || seconds == 22 || seconds == 32 {
		fmt.Printf("nd")
	} else if seconds == 3 || seconds == 23 {
		fmt.Printf("rd")
	} else {
		fmt.Printf("th")
	}

	//Prints the current time in hours and minutes and the activity to be done.
	fmt.Println(" hour: Klockan är", time.Now().Format("15:04"), ":", a)
	go Remind(a, delay)
}

func main() {

	//All the activities that should be done.
	var a string = "Dags att äta"
	var b string = "Dags att arbeta"
	var c string = "Dags att sova"

		//Sends the activity and the duration.
		go Remind(a, 1)
		go Remind(b, 3)
		go Remind(c, 5)
	select {}
}
