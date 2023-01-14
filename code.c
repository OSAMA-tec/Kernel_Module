#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

// Define the struct birthday
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

// Declare and initialize the list head
static LIST_HEAD(birthday_list);
// Function to create the linked list
void create_list(void) {
    int i;
    // Allocate memory for 5 struct birthday elements
    for (i = 0; i < 5; i++) {
        struct birthday *person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i + 1;
        person->month = i + 1;
        person->year = 2000 + i;
        INIT_LIST_HEAD(&person->list);

        // Add the element to the end of the list
        list_add_tail(&person->list, &birthday_list);
    }

    printk(KERN_INFO "Linked list created\n");
}

// Function to traverse the linked list
void traverse_list(void) {
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "day: %d, month: %d, year: %d\n", ptr->day, ptr->month, ptr->year);
    }
}

// Function to remove a specific element from the list
void remove_element(int year) {
    struct birthday *ptr, *next;
    // Traverse the list and remove the element with a matching year
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        if (ptr->year == year) {
            list_del(&ptr->list);
            kfree(ptr);
            break;
        }
    }
}

int init_module(void) {
    create_list();
    traverse_list();
    return 0;
}

void cleanup_module(void) {
    remove_element(2002); // remove element with year 2002
    // struct birthday *ptr, *next;
    // // Traverse the list and remove each element
    // list_for_each_entry_safe(ptr, next, &birthday_list, list) {
    //     list_del(&ptr->list);
    //     kfree(ptr);
    // }

    printk(KERN_INFO "Linked list removed\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Osama Alishba Hafsa");
MODULE_DESCRIPTION("A simple kernel module that creates, traverses, and removes a linked list");
