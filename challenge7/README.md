1. start
2. Enter N
3. Check if N is between 5 and 15. Otherwise, go to step 2
4. Enter N ticket IDs into a one-dimensional array
5. Validate all IDs by checking that they belong to the range [1…N]. Otherwise, go to step 4
6. Print the input scan sequence
7. Validate each of IDs from 1 to N by comparing it with all elements in the array
8. Find occurrence number for each ID
9. Identify those IDs which have occurred zero times as missing
10. Identify those IDs which have occurred two times as duplicated
11. Check if the log has any IDs other than exactly one missing ID and exactly one different duplicated ID. Otherwise, print the message about invalid-log
12. For each element check if it is larger than those elements which are to the right of it and calculate how many such pairs there are
13. Extract the last two numeric digits R of your registration number
14. Calculate Target = (R % N) + 1
15. Output all one-based positions of the target ID and its occurrence count
16. Print the count of out-of-order pairs
17. stop
