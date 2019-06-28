# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An invented long word refering to a disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

getrusage stands for get resource usage and returns resource usage measures for the calling process, the children of the calling process
or the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

2 structs and 13 long types

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

 Passing structs by value takes up a lot of memory especially if structs are large like in this case; this comes about as a result of
 of the copies made of the structs which get placed in the stack and can potentially cause stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The 2nd or 3rd argument is the text file. A pointer is set to a file which is opened in readmode. Main also checks if pointer is pointing to a null character in which case main gives an error.
Four variables are defined: "index" keeps track of the position in the word, "misspellings" tracks the amount of words misspelt ie are not in the dictionary, "words" is an int storing number of
words read for misspellings, "word" is the character set equal to the maximum size of a word plus one character marking end of string. The loop goes through each character until cursor is at end
of file. The loop ignores numbers. If the cursor is refering to an alphabet or apostrophe following an alphabet then the character is added to the variable word in the index position that the loop is using. The index is
incremeneted by 1 to store the next character in the i+1 position. Another condition following these checks that the word is not too long in which case loop passes through word without storing it and essentially ignores it
setting index back to 0. The cursor is at end of a word if the character is not alphabetical or an apostrophe or a number.
The wrod counter is incremented by 1 marking the addition of a word which is then passed to check for mispelling.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Where fgetc reads the file character by character able to detect any non-alphabetical, fscanf reads until a blank, newline or tab is encountered(whitespace)
storing these characters in the array in a buffer. The problem arises because the words in text file have commas at end which would be considered part of the word and stored
and cause problems for the misspelling function.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

In order to ensure that there are no changes in the words read and the dictionary being used. It's important to make the values
consistent which is done by ensuring that the initial value of the parameter cannot be modified.
