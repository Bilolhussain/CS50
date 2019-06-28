# Z++

## Questions

1.

```
function subtract($x, $y)
{
    //subtract y from x
    $x <- add($x, -$y)
    return($x)
}
```

2.

```
function multiply($x, $y)
{
    //assign value 0 to a
    $a <- 0
    //checks if x is greater than 0
    if(0 < $x)
    {
        //checks if y is greater than 0
        if (0 < $y)
        {
            //as long as x-y is less than x
            while(subtract($x, $y) < $x)
            {
                //y is reduced by 1
                $y <- subtract($y, 1)
                //a is added to x each time the loop runs
                $a <- add($a, $x)

            }
            return($a)

        }
        //if y is 0 then it returns 0
        return ($a)

        //checks if y less than 0
        if ($y < 0)
        {
            while(add($x, $y) > y)
            {
                $x <- subtract($x, 1)
                $a <- add($a, y)
            }
            return($a)
        }

    }
    return ($a)
    //checks if x is neagtive
    if($x < 0)
    {
        //checks if y is negative
        if($y < 0)
        {
            while(add($x,$y) < $x)
            {
                $y <- add($y, 1)
                $a <- subtract($a, $x)
            }
            return($a)
        }
        //checks if y is positive
        if($y > 0)
        {
            while(add($x, $y) > x)
            {
                $y <- subtract($y, 1)
                $a <- add($a, x)
            }
            return($a)
        }
    }


}
```

3.

```
function multiply($x, $y)
{
    //checks if x is not equal to 0
    if($x)
    {
        //base case
        if (0 < $y )
        {
            //value of y decreases with each addition
            $y <- subtract($y, 1)
            //recursively adds x until y = 0
            return (add($x, multiply($x, $y)))
        }
        return (0)


        //if y is negative
        //base case
        if($y < 0)
        {
            $y <- add($y, 1)
            //recursively add y until y reaches base case
            return (add(-$x, multiply($x, $y)))
        }return (0)

    }return (0)
}
```

## Debrief

1. https://www.youtube.com/watch?v=2kYeQPN3FNc
   https://www.youtube.com/watch?v=VrrnjYgDBEk

2. 4 hours
