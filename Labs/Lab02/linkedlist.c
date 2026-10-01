#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

// Note: this may look like a constant based on naming convention, but without
// `const`, it's actually declared as a global variable
int kNumElements = 20;

struct Node *make_list()
{
    // Make a list with one element
    struct Node *front = malloc(sizeof(struct Node));
    front->value = 0;
    front->next = NULL;

    struct Node *end = front;
    // Tack on 19 elements to the end of the list
    for (int i = 1; i < kNumElements; i++)
    {
        // Allocate a node and add it to the end of the list
        end->next = malloc(sizeof(struct Node));
        // Now, this new node is the end of the list
        end = end->next;
        // Initialize the new node
        end->value = i;
        end->next = NULL;
    }

    return front;
}

void swap_tenth_node(struct Node *list)
{
    // Go to the 10th node
    struct Node *curr = list;
    for (int i = 0; i < 10; i++)
    {
        curr = curr->next;
    }

    // Replace the next node
    struct Node *nextNext = curr->next->next;
    curr->next = malloc(sizeof(struct Node));
    curr->next->next = nextNext;
    curr->next->value = 100;
}

/**
 * Program is going to create a linked list with 20 nodes. Then, it will
 * replace the 10th node with a different one, and finally print/free the list.
 */
int main()
{
    struct Node *list = make_list();

    // Swap a node
    swap_tenth_node(list);

    /* Print and free everything */
    struct Node *curr = list;
    while (curr->next != NULL)
    {
        printf("%d\n", curr->value);
        struct Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

/*
    3.a: There are two memory bugs. First, in swap_tenth_node(),
    the original 11th node is no longer reachable after curr->next
    is replaced, so it becomes a memory leak; fix it by saving the
    old node and freeing it, e.g. struct Node *old = curr->next;
    curr->next = malloc(sizeof(struct Node)); ... free(old);.

    Second, in main(), the loop only frees nodes while curr->next != NULL,
    so the last node is never freed, causing another memory leak; fix it with while
    (curr != NULL) { struct Node *next = curr->next; free(curr); curr = next; }.

    3.b: Clang-Tidy may not reliably detect either leak because detecting dynamically
    allocated memory that becomes unreachable requires interprocedural/control-flow reasoning;
    some warnings may also be false positives, so its output should be interpreted carefully.

    3.c: LeakSanitizer should detect both leaks at program termination, because the allocated
    nodes remain unreachable/not freed; AddressSanitizer itself primarily detects invalid memory
    accesses rather than ordinary leaks, while LeakSanitizer is specifically designed to detect these leaks.


    4.d: Yes, the fuzzer should eventually find the leak because it can
    generate an input such as [a, which reaches the close_bracket == NULL
    branch where mutable_copy and key are not freed. With LeakSanitizer
    enabled through -fsanitize=fuzzer,address,undefined, the fuzzer reports
    the memory leak and saves the triggering input in a corpus/crash artifact,
    which can then be used to reproduce the problem. This demonstrates why
    fuzzing is useful for dynamic analysis: instead of manually guessing
    an input such as [a, LibFuzzer automatically explores many inputs and
    tries to reach previously unexplored execution paths; however, fuzzing
    is still not a proof that all memory bugs have been found because it only
    detects bugs in paths it actually exercises.
*/
