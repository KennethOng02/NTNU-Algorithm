|Algorithm|Best Case|Worst Case|Average Case|
|-|-|-|-|
|Bubble Sort||$n^2$||
|Selection Sort||$n^2$||
|Merge Sort||$nlogn$||
|Quick Sort|$nlogn$|$n^2$|$nlogn$|

#### Randomized Quick Sort
Partition around a random element\
Avoid worst case
```
ALGORITHM RANDOM-QUICKSORT(A, p, r)
if p < r
  q = RANDOM-PARTITION(A, p, r)
  QUICKSORT(A, p, q-1)
  QUICKSORT(A, q+1, r)
```

```
ALGORITH RANDOM-PARTITION(A, p, r)
i = RANDOM(p, r)
```
