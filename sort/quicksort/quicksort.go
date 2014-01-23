package main

import(
    "fmt"
    "time"
    "math/rand"
)
func quicksortproxy(a []int, n int) {
    quicksort(a, 0, n - 1)
}

func quicksort(a []int, left, right int) {
    i := left
    j := right
    key := a[left]
    p := left
    for i <= j {
        for j >= p && a[j] >= key {
            j--
        }
        if j >= p {
            a[p] = a[j]
            p = j
        }
        for i <= p && a[i] <= key {
            i++
        }
        if i <= p {
            a[p] = a[i]
            p = i
        }
    }
    a[p] = key

    if p - left > 1 {
        quicksort(a,left, p - 1)
    }

    if right - p > 1 {
        quicksort(a, p + 1, right)
    }
}

func main() {
    var a []int
    for i := 0; i < 1000; i++ {
        a = append(a,rand.Int() % 1000)
    }

    start := time.Now()
    quicksortproxy(a,1000)
    end := time.Now()
    fmt.Println(end.Sub(start))

    fmt.Println(a)
}
