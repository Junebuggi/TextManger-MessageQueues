Assignment 3: Text Management System (Using Message Queues)
Name: Emma Boulay

Note: Punctuation is allowed inside the sentence, I have created a
function that will account for that. If the word applesauce is in
the sentence and you try to remove apple, applesauce will not be removed,
there are no partial matches only full matches. As well you can try to pass
more than 1 sentence to append at a time, each sentence will be stored in its
own node in the linked list. If you did not include a '.', '?' or '!' at the end of your
sentence to append, a period will be added by default. A sentence may only end in
'.', '?' or '!'

Note 2: I have provided use of command line arguments that will read in from the
text files provided to test the system. If no cmd line args provided you will have
to type in the commands and parameters to pass to the text manager from the user.

Note 3: The max character length that can be passed from the user to the text-manager
is 35.

Set-Up Instructions:
1. Run the makefile to compile:
	$ make
2. Run the program with inputTest1 to test the append function :
	$ ./textManager
	$ ./user appendTest  (in new window)
3. Run the program with inputTest2 to test the delete function :
	$ ./textManager
	$ ./user deleteTest  (in new window)
4. Run the program with inputTest3 to test the remove function :
	$ ./textManager
	$ ./user removeTest  (in new window)
5. Run the program with inputTest4 to test the search function :
	$ ./textManager
	$ ./user searchTest  (in new window)
6. Run the program with inputTest5 to test all functions :
	$ ./textManager
	$ ./user allTest  (in new window)
7. Run the program to test user-input functionality :
	$ ./textManager
	$ ./user             (in new window)

********** Average Time for Each Command ***********/
The allTest test (number 7) was run 10 times. With its
averages calculated below;

Average time for append operation: 0.44 ms
Average time for delete operation: 2.33 ms
Average time for remove operation: 2.80 ms
Average time for search operation: 4.06 ms

/********** Discussion of Test Results ***********/
My assignment has a user process that is in charge of sending user commands
and parameter sentence and words to the Text-manager. And the Text-Manager
process is in charge of receiving and executing the user's commands on the
text stored in the Text-Manager. The search operation takes the longest to
execute with an average of 4.06 seconds. The append operation executes the
fastest with an average execution time of 0.44 seconds. Each sentence in the
text-manager is stored as a node in a singly-linked list, this makes it easier
to return or delete a sentence (ie a node) in the text-manager. The append
operation takes the shortest time to execute because all the other functions
search through each sentence, whereas append just needs to travers to the last
node.

================== Test 1 : Testing Append ==================
User Output:
_____________________________
Enter a command call: append
Enter a sentence to append to Text-Manager: Nobody met the efficient soup.
Enter a command call: append
Enter a sentence to append to Text-Manager: The plain move measures branch.
Enter a command call: append
Enter a sentence to append to Text-Manager: Overt interest flowers crazy.
Enter a command call: append
Enter a sentence to append to Text-Manager: The technical repair.
Enter a command call: append
Enter a sentence to append to Text-Manager: Imagines the cavernous economy.
Enter a command call: append
Enter a sentence to append to Text-Manager: The cold state ate the final.
Enter a command call: append
Enter a sentence to append to Text-Manager: The dazzling gas ate the address.
Enter a command call: append
Enter a sentence to append to Text-Manager: Existing is the prior.
---------------------------------
Text-Manager Output:
Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.The cold state ate the final.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.The cold state ate the final.The dazzling gas ate the address.

Command received: append
Message from user appended
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.The cold state ate the final.The dazzling gas ate the address.Existing is the prior.

Command received: exit

Average time for append operation: 0.44 ms

================== Test 2 : Testing Delete ==================
//Note: assumes Test1 has already been appended to Text-Manager
User Output:
_____________________________
Enter a command call: delete
Enter a word to delete from Text-Manager: world
Enter a command call: delete
Enter a word to delete from Text-Manager: the
Enter a command call: delete
Enter a word to delete from Text-Manager: ate
Enter a command call: delete
Enter a word to delete from Text-Manager: flowers
Enter a command call: delete
Enter a word to delete from Text-Manager: technical
Enter a command call: delete
Enter a word to delete from Text-Manager: move
---------------------------------
Text-Manager Output:
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.The cold state ate the final.The dazzling gas ate the address.Existing shake slapped the prior.
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met  efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines  cavernous economy.The cold state ate  final.The dazzling gas ate  address.Existing shake slapped  prior.
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met  efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines  cavernous economy.The cold st   final.The dazzling gas   address.Existing shake slapped  prior.
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met  efficient soup.The plain move measures branch.Overt interest  crazy.The technical repair.Imagines  cavernous economy.The cold st   final.The dazzling gas   address.Existing shake slapped  prior.
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met  efficient soup.The plain move measures branch.Overt interest  crazy.The  repair.Imagines  cavernous economy.The cold st   final.The dazzling gas   address.Existing shake slapped  prior.
Command received: delete
All occurrences of user-word deleted
String stored in Text-Manager is now:
Nobody met  efficient soup.The plain  measures branch.Overt interest  crazy.The  repair.Imagines  cavernous economy.The cold st   final.The dazzling gas   address.Existing shake slapped  prior.
Command received: exit

Average time for delete operation: 2.33 ms

================== Test 3 : Testing Remove ==================
//Note: assumes Test1 has already been appended to Text-Manager
User Output:
_____________________________
Enter a command call: remove
Enter a word to remove the first sentence containing the word from Text-Manager: ate
Enter a command call: remove
Enter a word to remove the first sentence containing the word from Text-Manager: flowers
Enter a command call: remove
Enter a word to remove the first sentence containing the word from Text-Manager: technical
Enter a command call: remove
Enter a word to remove the first sentence containing the word from Text-Manager: move
Enter a command call: remove
Enter a word to remove the first sentence containing the word from Text-Manager: the
---------------------------------
Text-Manager Output:
Command received: remove
First occurrence of target sentence removed
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Overt interest flowers crazy.The technical repair.Imagines the cavernous economy.The dazzling gas ate the address.Existing shake slapped the prior.

Command received: remove
First occurrence of target sentence removed
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.The technical repair.Imagines the cavernous economy.The dazzling gas ate the address.Existing shake slapped the prior.

Command received: remove
First occurrence of target sentence removed
String stored in Text-Manager is now:
Nobody met the efficient soup.The plain move measures branch.Imagines the cavernous economy.The dazzling gas ate the address.Existing shake slapped the prior.

Command received: remove
First occurrence of target sentence removed
String stored in Text-Manager is now:
Nobody met the efficient soup.Imagines the cavernous economy.The dazzling gas ate the address.Existing shake slapped the prior.

Command received: remove
First occurrence of target sentence removed
String stored in Text-Manager is now:
Imagines the cavernous economy.The dazzling gas ate the address.Existing shake slapped the prior.

Average time for remove operation: 2.80 ms

================== Test 2 : Testing Search ==================
//Note: assumes Test1 has already been appended to Text-Manager
Enter a command call: search
Enter a word to search for in Text-Manager: Hello
Text manager returned the following sentence
Does not contain string!
Enter a command call: search
Enter a word to search for in Text-Manager: ate
Text manager returned the following sentence
The cold state ate the final.
Enter a command call: search
Enter a word to search for in Text-Manager: flowers
Text manager returned the following sentence
Overt interest flowers crazy.
Enter a command call: search
Enter a word to search for in Text-Manager: cavernous
Text manager returned the following sentence
Imagines the cavernous economy.
Enter a command call: search
Enter a word to search for in Text-Manager: doesNotConatain
Text manager returned the following sentence
Does not contain string!
Enter a command call: search
Enter a word to search for in Text-Manager: measures
Text manager returned the following sentence
The plain move measures branch.
Enter a command call: search
Enter a word to search for in Text-Manager: the
Text manager returned the following sentence
Nobody met the efficient soup.
Enter a command call: search
Enter a word to search for in Text-Manager: state
Text manager returned the following sentence
The cold state ate the final.
---------------------------------
Text-Manager Output:
Command received: search
User string could not be found

Command received: search
Sentence found and sent to user

Command received: search
Sentence found and sent to user

Command received: search
Sentence found and sent to user

Command received: search
User string could not be found

Command received: search
Sentence found and sent to user

Command received: search
Sentence found and sent to user

Command received: search
Sentence found and sent to user

Command received: exit

Average time for search operation: 4.06 ms
