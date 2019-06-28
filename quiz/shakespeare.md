# To be or not to be

## ~~That is the question~~ These are the questions

4.1. 1000

4.2. For the length of self.genes which is a list of characters, compare elements in the list with the string
     target in such a way that score is incremented if for a certain position the character in list is equal
     to the character in target. The ratio of this score to the length of the target string gives the fitness.

4.3. score = 3 so fitness = 3/18 = 1/6

4.4. To calculate fitness we need to find where the number of operations required to convert a character to
     match the target character is 0. So, for the length of targetted string, increment score whenever edit distance
     between two strings = 0 and use this score afterwards in the same way as the given code does.

4.5. Mutation in this case is used to ensure that characters which could not be inherited in the child's design
     from the parents pool(excluded in the selection process or after crossover)but might be present in target string
     could still be used/compared by mutating in some childs' design. Mutating here is the adding of a random
     character to ensure our algorithm doesn't get stuck in case it's missing a certain character.

## Debrief

a. https://en.wikipedia.org/wiki/Edit_distance

b. 60 minutes
