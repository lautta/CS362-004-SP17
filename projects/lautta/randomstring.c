/***********************************
* August Lautt
* lautta
* CS 362
* Quiz 2
************************************/

/*

For this task, I recognized that to produce the error message, first inputChar() had to 
produce very specific characters in a specific order to reach the next state. Then 
inputString() had to produce the string “reset\0” after the state reached 9. So I worked 
backwards from that. Originally I implemented a solution that took the range of possible 
ASCII characters for both inputChar and inputString and picked random chars for both 
from that same range but these tests would not finish or took forever to run. Then I 
implemented only the specific ranges of chars for each inputChar and inputString to pick 
randomized ASCII values but this was also taking a long time to run.

So finally, I decided to limit the possible chars further to just the specific required 
chars for each function. I created arrays with those characters for each function and 
randomly chose one to return. This still creates random output and it is clear from the 
test that only the specific output required will work, so it isn’t really necessary to 
test characters other than those required. I also decided to randomize the null 
terminator for inputString since it was the final test step. This caused my 
implementation to run at a more randomized range of iterations that sometimes took much 
longer to run than if I simply added the terminator to the end of every return value of 
inputString but I felt it was more in the spirit of the random test. My implementation 
of inputChar randomly picks a value from the char array of potential ASCII values until 
the correct value is picked for the current stage. This occurs until the stage reaches 9. 
Then inputString randomly chooses chars from the char array of potential values and puts 
them into a string to return until "reset/0" is produced while the stage is 9. My 
implementation returns the error message with exit status 200 in a range of 
1500 – 30000 iterations.

*/