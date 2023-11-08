# cpu-prefetch-exp

This is an example to show what's the difference between using list and vector to save points for game objects.

From this experiment, we can see that when updating the world matrix for a game object tree (depth: 10, each parent has 100 children), list (linked list) always needs more time than vector (array).

## Results (Time)

The execution time for updating 10 times.

|Time|Linked List|Array|
|:----:|:----:|:----:|
|1|25.489 ms|16.502 ms|
|2|25.366 ms|16.424 ms|
|3|25.466 ms|16.886 ms|
|4|24.962 ms|17.028 ms|
|5|25.165 ms|16.441 ms|
|6|25.686 ms|16.775 ms|
|7|26.696 ms|17.073 ms|
|8|25.633 ms|16.695 ms|
|9|25.300 ms|16.662 ms|
|10|26.022 ms|16.916 ms|
|----|----|----|
|Avg.|25.579 ms|16.740 ms|

## Results (FPS)

Convert it to fps.

|Time|Linked List|Array|
|:----:|:----:|:----:|
|1|39.2 fps|60.6 fps|
|2|39.4 fps|60.9 fps|
|3|39.3 fps|59.2 fps|
|4|40.1 fps|58.7 fps|
|5|39.7 fps|60.8 fps|
|6|38.9 fps|59.6 fps|
|7|37.5 fps|58.6 fps|
|8|39.0 fps|59.9 fps|
|9|39.5 fps|60.2 fps|
|10|38.4 fps|59.1 fps|
|----|----|----|
|Avg.|39.1 fps|59.8 fps|
