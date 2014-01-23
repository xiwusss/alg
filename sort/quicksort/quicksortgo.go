package main

import (
	"sort"
    "fmt"
    "time"
    "math/rand"
)



func main() {
    var a []int
    for i := 0; i < 1000; i++ {
        a = append(a,rand.Int() % 1000)
    }
    start := time.Now()
	sort.Ints(a)
    end := time.Now()
    fmt.Println(end.Sub(start))
    fmt.Println(a)
}
