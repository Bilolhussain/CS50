# Helping `help50`

## Questions

1. The remainder operator % only operates on integer types like short, int, double etc, whereas in this case we are using it on two floats
    which is why there is an error.

2. The get_string is missing the size brackets and currently is void. It should be string input = get_string();

3. Buffer type should be unsigned char and not char since signed char which is causing the error can only take values of -128 to 127 wherease 0xff is 255
   and as such is out of bounds of the current signed buffer.

4. Since the node is an array there must be size identified shown by having brackets after root. The code should look like
   node* root[] = {false, {NULL}};

## Debrief

1. https://stackoverflow.com/questions/38302220/error-when-comparing-array-elements-to-constant-c

2. 40 min
