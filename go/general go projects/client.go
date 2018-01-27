package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"time"
	"sync"
)

func main() {
	server := []string{
		"http://localhost:8080",
		"http://localhost:8081",
		"http://localhost:8082",
	}

	// Add a time limit for all requests made by this client.
	//Clients have 5 seconds to respond with a temperature value.
	client := &http.Client{Timeout: 5 * time.Second}

	for {
		before := time.Now()
		//res := Get(server[0], client)
		res := MultiGet(server, client)
		after := time.Now()
		fmt.Println("Response:", res)
		fmt.Println("Time:", after.Sub(before))
		fmt.Println()
		//Every 2th second, a new search for the temperature will take place.
		time.Sleep(2000 * time.Millisecond)
	}
}

type Response struct {
	Body string
	StatusCode int
}

func (r *Response) String() string {
	return fmt.Sprintf("%q (%d)", r.Body, r.StatusCode)
}

// Get makes an HTTP Get request and returns an abbreviated response.
// The response is empty if the request fails.
func Get(url string, client *http.Client) *Response {
	res, err := client.Get(url)
	if err != nil {
		return &Response{}
	}
	// res.Body != nil when err == nil
	defer res.Body.Close()
	body, err := ioutil.ReadAll(res.Body)
	if err != nil {
		log.Fatalf("ReadAll: %v", err)
	}
	return &Response{string(body), res.StatusCode}
}

// MultiGet makes an HTTP Get request to each url and returns
// the response from the first server to answer with status code 200.
// If none of the servers answer before timeout, the response is 503
// – Service unavailable.
func MultiGet(urls []string, client *http.Client) (res *Response) {
	response := make(chan *Response, len(urls))
	wg := new(sync.WaitGroup) //Create a wait-group for all the servers
	wg.Add(len(urls))
	for _, url := range urls {
		go func(url string) { //Will simultaneously ask all the servers after the temperature.
			get := Get(url, client)
			if get.StatusCode == 200 { //If temperature is found, terminate the search.
				response <- get
			}
			wg.Done()
			wg.Wait()
			//Else, terminate the search after 5 seconds and print out "Service Unavailable".
			response <- &Response{"Service Unavailable", 503}
		}(url)
	}
	res = <-response
	return
}