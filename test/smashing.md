# Stack Smashing

## Questions

1. In a stack frame, a canary value precedes the return address(which should stay same during execution of function) and since we know the value stored in the address before return is reached
   we can check if that value changed during the execution of a function. The value being changed serves as a warning letting the programmer know that
   due to buffer overflow the return address has been rewritten.

2. It comes from "canary in a coal mine" where canary is a warm-blooded animal which detects CO and warns the miners about toxic gases which is
   similar to the role served by the canary value in a stack since it warns the programmer that buffer overflow, causing certain values to be written
   in addresses where they weren't supposed to be like the return address which shouldn't have been changed, has occured.

3.
    int Last(int n)
    {
        char buffer[n];
        for(int i = 0; i <= n; i++)
        {
            buffer[i] = i;
            return buffer[n];
        }
    }


## Debrief

1. https://en.wikipedia.org/wiki/Stack_buffer_overflow
   https://www.youtube.com/watch?v=uSC3guWOvpk
    https://en.wikipedia.org/wiki/Sentinel_species#Historical_examples

2. 40 min
