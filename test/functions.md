# #functions

## Questions

1. The hash is slow because it maps the string using only the first letter in the element which means there would be a lot of
   collisions causing each bucket of hashtable to hold several string that have been mapped to the same hashtable bucket by the hash.
   As we know hashtable loses its effectiveness in that case since long linked lists would need to be checked one after the
   other for different operations.

2. Hash is perfect by definition because it maps distinct string of characters to set of integers without any collisions as the hash is the decimal
   value of the binary representation of the character or string being hashed. However, it's not perfect for c because of how long the hash
   value would be of string with more than 4 characters. C can not handle very large hash values as it won't be able to
   store it in an 32 or 64 bit integer. They are also too big to store in a double - a double is not accurate enough to store every single digit.

3. CS50's solution uses hash function which works in constant time as having the hexadecimal with a unique index makes access and other
   operations efficient. If the hashes were stored in the 50 image files, each of the files would need to be opened first to access the hash(hexadecimal string) and then compare it with the
   the hash for the student's image file. Before the next recovered image file's hash can be compared(which requires opening a new file) with the staff's hash,
   the first JPEG file would need to be closed and this would slow down the time to check the recovered files. Moreover, the hexadecimal hash would need to be stored everytime
   somewhere everytime it is accessed from a file for the comparison.
   of in

4. For a hashtable in worst case, collision can result in several objects being placed in the same hash which might have a linked list structure
   that requires going through each element in the bucket to check whether the object is the one needed thus we lose random access. However, in a trie, there is no hash applied and for any word
   the lookup relies on following a character by character approach to traverse the tree ensuring that the time complexity is O(1) where the 1 represents the length
   of the word/key being found as such it's constant time. Unlike Hashtables, lookup in trie is independant of other objects since only in hash
   are objects need to be compared one after the other until the one we are looking for is found(in case of collisions and large data set).

## Debrief

1. https://en.wikipedia.org/wiki/Trie
    http://www.techcrashcourse.com/2015/11/Disadvantages-and-limitations-of-C-Programming-languages.html

2. 60 minutes
