# Now Boarding

## Questions

1.

```c
typedef struct
{
    int value;
    pqueue *lower;
    pqueue *higher;
}
pqueue;
```

2.  Define Pqueue as a node with members value and two pointers to lower and higher nodes. Check whether
3.  queue is empty. If the queue is not empty, malloc a newnode.
    Compare passenger->group with pqueue->value
    and check if the node should be placed lower or higher in priority. If a lower group is higher priority
    passenger->group is higher and (pqueue->value) is lower,
    store passenger->group at pqueue->higher.
    If a group is lower priority
    passenger->group is lower and (pqueue->value) is higher,store passenger->group at pqueue->lower where lower is a node  higher represents the new node creater with the item enqueued.
    Move current pointer to higher node(being created) or lower node depending upon whether
    the next node to be added is higher or lower in priority to the current node. The node added becomes the tail or head of the
    priority queue.

3.  O(n). Since in the worst case if we are at the node with lowest priority then each node in higher priority to that one would need
    to be compared with the new node(passenger) to enqueue until it is at the right level of priority. This might mean going through all the
    nodes once until the right position for the passenger is found.

4.  If queue is not empty do a while loop checking whether next (head) node is higher priority than the current node. Go to the group with highest priority by comparing current node with the one that's the head of the node and extract
    passenger->group from highest priority. If two passenger groups have same priority, extract the passenger first accessible in the
    queue. The node, prior to the one node from which passenger/value is removed, is given the the the highest priority. Then free the node from which data was extracted. Repeat this process for each
    node going from high priority to lower priority in comparison.


5.  Upperbound is O(n). Because unless the node to be removed is at the head or tail of the current node, each passenger's is compared
    one after the other until the highest priority is found and removed.

## Debrief

1. https://stackoverflow.com/questions/9460537/how-to-make-an-array-with-my-struct-types
   https://stackoverflow.com/questions/14048143/why-is-deleting-in-a-single-linked-list-o1

2. 3 hours
