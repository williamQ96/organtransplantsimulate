Overview

The goal of this project is simulating matching individuals for organ transplants. A transplant requires a recipient (R), a donor (D) with compatible blood type, and a surgeon (S) who is available to perform the procedure. Your goal is to read an argument-provided text file, where each line of the file represents the event of a new recipient, donor, or surgeon becoming available, listed in chronological order (top-to-bottom). We will assume that transplants should occur on a first-come, first-served basis. This suggests using a queue-based approach, and you must implement queues to receive credit for this project.

Let's consider the first three lines in the sample file as an example:

R:AB:Aubrey Madison

This line depicts a new organ recipient (R), with blood type AB, named Aubrey Madison. That is, this is an individual who is newly in need of receiving an organ.

D:O:Dakota Dyson

This line depicts a new organ donor (D), with blood type O, named Dakota Dyson. That is, this is an individual who is newly available for donating an organ.

S:Sam Khyvrych

This line depicts a surgeon (S) named Sam Khyvrych who has appointment availability for performing an organ transplant.

After processing the first two lines, your program should deduce while processing the third line that the recipient and donor are available and compatible, and immediately match them with the newly-available surgeon. (Details will be given below.) Your program will then continue to process the remaining lines in the file.

As shown, each line comprises colon-separated values, and each line can have either three or two values:

The first value on a line is one of the characters R, D, or S.
If the first character on a line is R or D, then there are two additional values:
The second value is the individual's blood type, which can be AB, B, A, or O.
The third value is the individual's name.
If the first character on a line is S, then the second value is the surgeon's name.
You will need nine distinct queues:

Four queues for recipients, where each queue respectively represents one of the four blood types.
Four queues for donors, where each queue respectively represents one of the four blood types.
One queue for surgeons.
The starter code provides suggested declarations for declaring "recipients" and "donors" arrays, where each element is a queue. This way, the four queues for recipients are accessible by the "recipients" array, and similarly for donors.

Prescribed Program Flow

Below is a prescribed flow for your program; following this flow will make correct implementation easier, and details will be described next.

Flow

Read the file one line at a time, performing the below steps immediately for each line.
Parse the current line to identify its values.
If the line represents a recipient, do not immediately enqueue the recipient. Instead, do this:
Check to see if a compatible donor, and a surgeon, are both available and waiting in a queue.
If so, dequeue the donor and surgeon and print the match.
If not, then enqueue the recipient.
If the line represents a donor, perform similarly as with recipients (except with the donor and recipient roles reversed).
If the line represents a surgeon, do not immediately enqueue the surgeon. Instead, do this:
Check to see if a recipient and donor are both available and waiting in a queue (more details on this below).
If so, dequeue the recipient and donor and print the match.
If not, then enqueue the surgeon.
Blood Type Compatibility

Here is a general overview of recipient–donor compatibility based on blood types:

A recipient with blood type AB is compatible with a donor of any blood type.
A recipient with blood type B is compatible with a donor who has blood type B or O.
A recipient with blood type A is compatible with a donor who has blood type A or O.
A recipient with blood type O is compatible with a donor who has blood type O only.
A helper function has been provided in the starter code for ascertaining blood type compatibility.

Important Matching Details

Blood types demonstrate a matching challenge. For example, if a donor with blood type O and another donor with blood type AB are both queued, and a recipient with blood type AB arrives, both donors are compatible with the recipient. Which donor should provide the transplant? Here is an example of the dilemma:

O donors can be matched with any recipient, so they have a high likelihood of providing a transplant.
AB donors must be matched with AB recipients, so they have a low likelihood of providing a transplant.
If the O donor goes to the AB recipient, there is a chance that the AB donor will never be matched.
If the AB donor goes to the AB recipient, we are guaranteed to match the O donor with any future recipient.
We want to make the most matches possible, so we should match the AB recipient with the AB donor.
This scenario suggests an ordering with which your program should attempt to find matches, so as to maximize the number of matches (and minimize the number of unmatched individuals):

A recipient with blood type AB is compatible with AB, B, A, and O donors, preferring matches in that order.
A recipient with blood type B is compatible with B and O donors, preferring matches in that order.
A recipient with blood type A is compatible with A and O donors, preferring matches in that order.
A recipient with blood type O is compatible with O donors.
The starter code provides a helper array containing blood types for facilitating this ordering.

There is one more consideration: If recipients and donors are both queued, and a surgeon arrives, which blood types should they try to match first in order to maximize the total number of matches? Similarly to the strategy described above, we should match the rarest blood types first. In the USA, the order of rarity from most rare to least rare (left-to-right), is as follows:

AB, B, A, O

The helper array for blood types in the starter code has this same ordering. One suggestion is to use the  "recipients" and "donors" arrays as declared in the starter code so that each element of the "recipients" array is a queue, and the queue indices in "recipients" correspond with each index in the blood types helper array. (Similarly for the "donors" array.)

For example, blood_types[0] is "AB" so recipients[0] would be the queue containing AB recipients.

Queue Implementation Requirements

There are two ways to implement queues under consideration: One that takes O(n) time to dequeue, and one that takes O(1) time (that is, using "front" and "back"). You must implement the O(1) version for full credit, but if you like, you can start with an O(n) version just to get your project moving.

Helper functions are provided for printing queue contents. See the commented code in main for example usage.

Additionally, you must use QUEUE_SIZE as defined in the starter code for your queue sizes. There will be a penalty for submitting a working solution with an increased QUEUE_SIZE. Note: If you are encountering queue-full problems, some likely issues are these:

Your queue implementation is not reusing recently available queue space.
Your program flow is not following the prescribed flow above (perhaps enqueuing when you don't need to enqueue).
Your matching approach is not following the preferred matching strategy above (that is, your approach is not maximizing the overall number of successful matches).
Getting Started

Here is a strategy for getting started with this project:

Implement the queue struct and functions outlined in the starter code, and test them by un-commenting the provided queue test code and compiling and running. This will help you see if your queue implementation appears to be running correctly.
Parse the values on each line into separate variables, and add some print statements with the information parsed from the line. Compile it and test it with the input file. This will help you see how to get the values from each line correctly. Note: You must not read the whole file into a buffer, only one line at a time.
Add comments that describe your strategy for processing each line. You can use the prescribed program flow above (recommended) but write it in your own words. This will help you develop an understanding and help keep track of what you want to do.
Start writing actual code underneath your comments, perhaps starting with processing recipients (because handling donors will be similar). Processing surgeons will be slightly different.
Uncomment the queue-printing code at the bottom of main. This code prints the end state of the queues, and is required by the checker script for validating your solution.
Input File, Correct Output, Starter Code, and Checker Script

The input file (3C-input.txt) seeks to simulate a real-world recipient:surgeon:donor ratio of roughly 10:5:3. (There will be recipients left waiting.)

The correct output file (3C-correct-output.txt) shows the expected matches and ending queue status.

The starter code (proj3C.c) provides nontrivial implementations and guiding comments.

After you have a working program that prints matches and the ending queue status, you can try the checker script (check-3C.sh) to see how your output matches the correct output.

Submission

Ensure your solution passes the checker script in your virtual machine, then submit your proj3C.c to Canvas.

Sources

Blood types: https://en.wikipedia.org/wiki/Blood_typeLinks to an external site.

Blood type rarity: https://web.archive.org/web/20110719200400/http:/bloodcenter.stanford.edu/about_blood/blood_types.htmlLinks to an external site.

Names: https://surnames.behindthename.com/names/tag/matronymicsLinks to an external site.

Transplant statistics: https://insights.unos.org/OPTN-metrics/Links to an external site.
