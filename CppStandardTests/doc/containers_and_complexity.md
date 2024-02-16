## Containers, their internal structure description and main operations complexity.

### Stack

FILO

O(1)

### Queue

FIFO

O(1)


### Vector

Based on array with additional size so will not relocate always.

| Operation | Complexity |
| - | - |
| add | O(1) |
| insert | O(n) |
| get | O(1) |
| find | O(n) |
| remove | O(n) |
| size | O(1) |
| clear | O(n) |


### deque

Array chunks combined in a list

| Operation | Complexity |
| - | - |
| add | O(1) |
| insert | O(n) |
| get | O(1) |
| find | O(n) |
| remove | O(n) |
| size | O(1) |
| clear | ? |


### list

| Operation | Complexity |
| - | - |
| add | O(1) |
| insert | O(1) |
| get | O(n) |
| find | O(n) |
| remove | O(1) |
| size | O(1) |
| clear | ? |


## set

Red Black Tree (self-balancing tree)

| Operation | Complexity |
| - | - |
| insert | O(log n) |
| get | O(log n) |
| find | O(log n) |
| remove | O(log n) |
| size | O(1) |
| clear | O(log n) |


## unordered set

Hash table

| Operation | Complexity |
| - | - |
| insert | O(1), O(n) in case of rehash |
| get | O(1), O(n) in case of rehash |
| find | O(1), O(n) in case of rehash |
| remove | O(1) |
| size | O(1) |
| clear | O(1) |


## map

Red Black Tree (self-balancing tree)

| Operation | Complexity |
| - | - |
| insert | O(log n) |
| get | O(log n) |
| find | O(log n) |
| remove | O(log n) |
| size | O(1) |
| clear | O(log n) |


## unordered map

Hash table

| Operation | Complexity |
| - | - |
| insert | O(1), O(n) in case of rehash |
| get | O(1), O(n) in case of rehash |
| find | O(1), O(n) in case of rehash |
| remove | O(1) |
| size | O(1) |
| clear | O(1) |