# Loop through Vector w/o using iterators
[Geeks-for-geeks](https://www.geeksforgeeks.org/how-to-iterate-through-a-vector-without-using-iterators-in-c/)
```cpp
for(auto itr : vector_name)
```
- itr is the value stored in vector which is used to traverse vectors.

## Updating values in vector
```cpp
for(auto &itr : vector_name)
```
- itr is an address to the value stored in vector which is used to traverse vectors.

## Float v.s. Double
| Type | Size |
| ---- | ---- |
| Float | 4 bytes |
| Double | 8 bytes | 
