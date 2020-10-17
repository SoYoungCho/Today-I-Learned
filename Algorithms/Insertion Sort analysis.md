# Problem Set #1 (Algorithms)

Department : Information Convergence (정보융합학부)  
Student ID : 2017204050  
Student Name : 조소영  

---

## Consider the insertion sort. Consider each input as a sequence of n distinct numbers. 

![](https://upload.wikimedia.org/wikipedia/commons/e/ea/Insertion_sort_001.PNG)
Above picture is the Example for Insertion Sort.
Reference of the image : https://upload.wikimedia.org/wikipedia/commons/e/ea/Insertion_sort_001.PNG

## 1. To show outputs and plots in the following problems, write your program with your comments.
#### Explain your program at least four lines. 


```python
def insertion_sort(array):
    for j in range(1, len(array)): # j takes value 1 to len(array)-1
        key = array[j] # array element except index 0 becomes key
        i = j-1 # initialize index i with the left element of j
        while(i>=0 and array[i] > key): # check conditions if sorted
            array[i+1] = array[i] # move once to the right
            i = i-1 # change comparing element index
        array[i+1] = key # put key index in correct place
    return array # return sorted array
```


```python
array = [2,9,8,6,3,1,4,5,7]
insertion_sort(array)
```




    [1, 2, 3, 4, 5, 6, 7, 8, 9]



I implemented this python code based on the pseudocode in our course slides and CLRS textbook.

The array index starts with 1 in the pseudocode, but since python's indexing starts with 0, the value of j begins with 1 in line 2. Also, the function range(*start*, *end*) of python returns collection from *start* up to *end*-1. For example, in line **for j in range(1, 5)**, j takes 1 to 4. Therefore in line 3, the element in the input array becomes **key** except the first element in index 0. In line 4, index *i* is initialized with the left element of *j*. 

In the *while* loop of line 5, check two conditions whether (1) the key is bigger than the elements sorted left or an element not sorted or (2) the comparing element index i is over the range of the array.

If these two conditions are satisfied, it means that the key element is smaller than the comparing element of sorted sub-array, or key element has to come at the front of the array. After properly sorted, i.e. correct index is found for key element to insert, then in line 8, the key element is inserted in the correct place of sorted sub-array. After the end of for loop, the whole array sorted is returned in line 9.

## 2. For each of the following inputs, explain and show your input and output using your program.

### (a) An input for the worst case  

As for insertion sort, the input for the worst case is when the array is sorted in the opposite order. (Descending order if the goal is to arrange in ascending order)


```python
array = [9,8,7,6,5,4,3,2,1] # input for the worst case
insertion_sort(array)
```




    [1, 2, 3, 4, 5, 6, 7, 8, 9]



The reason why the opposite order sorted array is the worst case for insertion sort is because every key element in the array is smaller than the array[i] in line 5, therefore runs while loop for every element in the array.

### (b) An input for the best case  

As for insertion sort, the input for the best case is when the array is sorted correctly. (Ascending order if the goal is to arrange in ascending order)


```python
array = [1,2,3,4,5,6,7,8,9] # input for the worst case
insertion_sort(array)
```




    [1, 2, 3, 4, 5, 6, 7, 8, 9]



The reason why the corrected sorted order array is the best case for insertion sort is because every key element in the array is bigger than the array[i](the left array of key) in line 5, therefore does not run the while loop.

### (c) A random input 


```python
import random
array = [random.randint(1,10) for i in range(10)]  
array # A random input with length 10
```




    [8, 7, 5, 4, 4, 5, 10, 3, 3, 4]




```python
insertion_sort(array)
```




    [3, 3, 4, 4, 4, 5, 5, 7, 8, 10]



For the random input, I used python's 'random' module and used random.randint() function. This randomly generates 10 random numbers. Reference for random function : http://blog.daum.net/sualchi/13720340

## 3. For each of the following cases, explain and plot the number of times that the inner (while) loop test is executed versus *n*.
#### Note that the loop test is executed one time more than the loop body. 


```python
def insertion_sort_count(array):
    count = 1 # initialize count as 1
    for j in range(1, len(array)):
        key = array[j]
        i = j-1
        while(i>=0 and array[i] > key):
            array[i+1] = array[i]
            i = i-1
            count += 1 # increase value of count by 1
        array[i+1] = key
    return count # return the number of times while loop was executed
```

The function **insertion_sort_count(array)** is the insertion sort implemented function (same with the function above) with few lines added and changed to count times 'while loop' test executed.

Therefore in line 2, *count* is a **variable to count the number of times while loop test is executed** and is initialized as 1 as the loop test is executed at least once. In line 9, after the execution of while loop body, the value of variable *count* is increased by 1. Also, this function returns the number of times the while loop test was executed; the value of variable *count*.

### (a) The worst case


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
count_list = [] # list to save while loop test executed times for each n
for n in range(1,1000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    array.sort(reverse=True) # sort n numbers in decreasing order for worst case
    count_list.append(insertion_sort_count(array)) # append the number in count_list
plt.plot(count_list) # plot the number of times
plt.title("Number of times Inner Loop test executed versus n (Worst Case)")
plt.ylim(0, 600000) # set y axis range as 600000
plt.show()
```


![png](output_26_0.png)


As for the worst case, I estimated the number of times the while loop test was executed in insertion sort from the array size of 1 to 1000. As the worst case for insertion sort is the case when the array is sorted in reverse order, I assumed that the arrays are given in ascending order. I randomly sampled *n* numbers and used *sort(reverse = True)* to make each array of size n to create the worst case.

The number of times while loop test was executed was returned from the function *insertion_sort_count()* and each count was appended in the list *count_list*. Then I plotted the list using the function *plot()* from matplotlib module.

The plot above is the result for the number of times the inner loop test was executed for each array of size *n* in worst cases - reverse sorted arrays. The number of executed times increases exponentially compared to the average case below ((c) The average case by using multiple random inputs).

For comparison with the average case, I have set the y-axis range from 0 to 600,000 for both the worst case and the average case. Although the array input size increases equally in both worst and average cases, the difference in the number of times the while loop test was executed is extremely large since the while loop runs for every element in the worst case.

- Reference for sorting array in reverse order : https://wikidocs.net/16041
- Reference for plotting the while loop test executed times : http://pythonstudy.xyz/python/article/407-Matplotlib-%EC%B0%A8%ED%8A%B8-%ED%94%8C%EB%A1%AF-%EA%B7%B8%EB%A6%AC%EA%B8%B0
- Reference for setting plot y axis range : https://kongdols-room.tistory.com/83

### (b) The best case


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
count_list = [] # list to save while loop test executed times for each n
for n in range(1,1000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    array.sort() # sort n numbers in ascending order for best case
    count_list.append(insertion_sort_count(array)) # append the number in count_list
plt.plot(count_list) # plot the number of times
plt.title("Number of times Inner Loop test executed versus n (Best Case)")
plt.show()
```


![png](output_30_0.png)


As for the best case, I also estimated the number of times the while loop test was executed in insertion sort for each array from the size of 1 to 1000. As the best case for insertion sort is the case when the array is sorted in ascending order, I assumed that the arrays are given in ascending order. I randomly sampled *n* numbers and used *sort()* to make each array of size n to create the best case.

Like I have mentioned above, the number of times while loop test was executed was returned from the function *insertion_sort_count()* and each count was appended in the list *count_list*. Then I plotted the list using the function *plot()* from matplotlib module.

The plot above is the result for the number of times the inner loop test was executed for each array of size *n* in best cases - properly sorted arrays. The number of executed times is equally same for all *n* from 1 to 1,000; resulting in constant function of 1. The reason is because since the given array of size n is already sorted, the conditions in line 6 of *insertion_sort_count()* are not satisfied thus does not run the while loop. Therefore, **the while loop test is executed only once and the loop body is not executed in the best cases.** 

### (c) The average case by using multiple random inputs 


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
count_list = [] # list to save while loop executed times for each n
for n in range(1,1000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    # For average case, the array is composed of multiple random n inputs, assumed not sorted
    count_list.append(insertion_sort_count(array)) # append the number in count_list
plt.plot(count_list) # plot the number of times
plt.title("Number of times Inner Loop test executed versus n (Average Case)")
plt.ylim(0, 600000) # set y axis range as 600000
plt.show()
```


![png](output_33_0.png)


As for the average case, I also estimated the number of times the while loop test was executed in insertion sort for each array from the size of 1 to 1000, but by **using multiple random inputs given not sorted**. Therefore I randomly sampled *n* numbers and did not sort in either direction.

Same as above, the number of times while loop test was executed was returned from the function *insertion_sort_count()* and each count was appended in the list *count_list*. Then I plotted the list using the function *plot()* from matplotlib module.

The plot above is the result for the number of times the inner loop test was executed for each array of size *n* in average cases - **randomly sampled and not assumed sorted**. The number of executed times increases over input size but the plot is not as exponential as (a) the worst case above.

For comparison with the worst case, I have set the y-axis range from 0 to 600,000 for both the worst case and the average case. Although the array input size increases equally in both worst and average cases, **the number of times the while loop test was executed is relatively smaller than the worst case.** The reason for the difference in number is because the while loop runs for every element in the worst case, but in average case, we can assume that the loop runs n/2 times on average.

If you see the y-axis of the plot above, even with the same increasing input of the array size, in array size (array length) 1000 the number of times that the inner loop test was executed is about the half of the worst case plot.

## 4. For each of the following cases, explain and plot the actual running time in your computer versus *n*.


```python
import time
def insertion_sort_estimate_time(array):
    start_time = time.time()
    for j in range(1, len(array)):
        key = array[j]
        i = j-1
        while(i>=0 and array[i] > key):
            array[i+1] = array[i]
            i = i-1
        array[i+1] = key
    end_time = time.time()
    running_time = end_time-start_time
    return running_time # return running_time of the function
```

This function *insertion_sort_estimate_time(array)* is to estimate the actual running time for each insertion sort with input size *n*. I used time module of python and estimated starting time in line 3, end time in line 11. If you subtract start time from end time, you can get the running time of the insertion sort. This function returns the *running_time* value.

Reference for estimating code running time : https://m.blog.naver.com/PostView.nhn?blogId=cjh226&logNo=221392127142&proxyReferer=https:%2F%2Fwww.google.com%2F

### (a) The worst case


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
time_list = [] # list to save insertion_sort running time for each n
for n in range(1,2000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    array.sort(reverse=True) # sort n numbers in decreasing order for worst case
    time_list.append(insertion_sort_estimate_time(array)) # append the running time in time_list
plt.plot(time_list) # plot the actual running time
plt.title("Actual running time versus n (Worst Case)")
plt.ylim(0, 1) # set y axis range equally in all cases for comparison
plt.show()
```


![png](output_40_0.png)


### (b) The best case


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
time_list = [] # list to save insertion_sort running time for each n
for n in range(1,2000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    array.sort() # sort n numbers in ascending order for best case
    time_list.append(insertion_sort_estimate_time(array)) # append the running time in time_list
plt.plot(time_list) # plot the actual running time
plt.title("Actual running time versus n (Best Case)")
plt.ylim(-0.5, 0.5)
plt.show()
```


![png](output_42_0.png)


As for the best case, I also estimated the actuall running time in insertion sort for each array from the size of 1 to 2000. As the best case for insertion sort is the case when the array is sorted in ascending order, I assumed that the arrays are given in ascending order. I randomly sampled *n* numbers and used *sort()* to make each array of size n to create the best case.

The running time was estimated and returned from the function *insertion_sort_estimate_time()* and each estimated time was appended in the list *time_list*. Then I plotted the list using the function *plot()* from matplotlib module.

The plot above is the result for the running time in insertion sort for each array of size *n* in best cases - properly sorted arrays. The running time is mostly the same for all *n* from 1 to 2,000. 

I have set the y axis range from -0.5 to 0.5 to show that is takes almost 0 seconds for insertion sort in best cases. The reason is because since the given array of size n is already sorted, the conditions while loop test of *insertion_sort_count()* are not satisfied thus does not run the while loop, and therefore takes constant time for the function.

### (c) The average case by using multiple random inputs


```python
import matplotlib.pyplot as plt # import library matplotlib to plot graph
time_list = [] # list to save insertion_sort running time for each n
for n in range(1,2000): # test insertion sort for 1000 numbers (increasing array size)
    array = [random.randint(1,n) for i in range(n)] # randomly sample n numbers
    # For average case, the array is composed of multiple random n inputs, assumed not sorted
    time_list.append(insertion_sort_estimate_time(array)) # append the running time in time_list
plt.plot(time_list) # plot the actual running time
plt.title("Actual running time versus n (Average Case)")
plt.ylim(0, 1) # set y axis range equally in all cases for comparison
plt.show()
```


![png](output_45_0.png)


As for the average case, I also estimated the running time in insertion sort for each array from the size of 1 to 2000, but by **using multiple random inputs given not sorted**. Therefore I randomly sampled *n* numbers and did not sort in either direction.

Same as above, the estimated running time for insertion sort was returned from the function *insertion_sort_estimate_time()* and each estimated time was appended in the list *time_list*. Then I plotted the list using the function *plot()* from matplotlib module.

The plot above is the result for the running time in insertion sort for each array of size *n* in average cases - **randomly sampled and not assumed sorted**. The number of executed times increases over input size but the plot is not as steep as (a) the worst case above, but the curve is much smoother.

For comparison with the worst case, I have set the y-axis range from 0 to 1 for both the worst case and the average case. Although the array input size increases equally in both worst and average cases, **the running time is relatively shorter than the worst case.** The reason for the difference in number is same as Number 3; it is because the while loop runs for every element in the worst case, but in average case, we can assume that the loop runs n/2 times on average.

If you see the y-axis of the plot above, even with the same increasing input of the array size, in array size (array length) 2000 the running time of the average case is about the half of the worst case plot.

### Write your computing environment (e.g., CPU, RAM, OS). 
- OS : Windows 10 Education 64bit (10.0, 빌드 18363)
- Processor : Intel(R) Core(TM) i7-8565U CPU
- RAM : 16GB (15.8GB available)
