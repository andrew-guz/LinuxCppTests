## Main ideas

- do less copy and new memory allocations
- use threads
- constexpr can speedup your code

## 2D array

Stored in memory linearly (row by row) so better visit all cells by columns and than by rows. This will be 30 times faster.
CPU works faster with linear memory (cache lines) than jumping from one point to another.

Also it does not matter will we work with all element in cache or only with some of them. Modify something in cache much mire cheaper that to put new data in cache from memory.

But this will work for simple operations done on memory variable. Complex operation can take so much time that missing cache value will give very low time effect.

## Instructions/branch predictor

Can "predict" next instruction and avoid jumps in branches so sorted data can be processed faster that not sorted.

Also works for virtual functions.

## One variable used by different threads

Since each core has it's own part of L1 cache, editing same values by different cores needs to copy that value to upper cache to provide it to other core L1 cache. So it can be easier to run work in sequence instead of parallel to modify same variable.

### false sharing

In upper example we can try to use different variables to be modified by different thread and still face the same problem. The reason for this is that variables are stored nearby and will be placed in one cache line so they will anyway have to be passed to another core...