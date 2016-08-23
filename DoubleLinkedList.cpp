/*
 *  Created on: May 19, 2016
 *  Author: Kieran Mackenzie
 *
 *  Implementation of a doubly linked list, that can reverse the list order, and swap adjacent elements
 */
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

//Node Declaration

struct node
{
    int number;
    struct node *next; // will point to the node ahead of it
    struct node *behind; // will point to the node behind of it
}*start;

class linkedList
{
    public:
	// our public methods
        void newNode(int);
        void add(int);
        void display();
        int size();
        void reverse();
        int swapElements(int,int,int);
        linkedList()
        {
            start = NULL;
        }
};

int main()
{
    int choice,sizeList,value,index1,index2,whatHappen;
    linkedList myList; // making the object linkedList

    	cout << "What would you want to be your first integer value in your list? " << endl;
    	cin >> choice;

    	myList.newNode(choice); //creating our list first

    	while(true)
    	{

			cout<<"What would you like to do to your DLL?" << endl;
			cout<<"1 to add(x), 2 to return size, 3 to print, 4 to reverse your list and 5 to swap two adjacent values and quit, 6 to quit" << endl;
			cin >> choice; // catching user input

			switch(choice)
			{
			case 1:
				cout << "What value do you want to add?" << endl;
				cin >> value; //accepting user input
				myList.add(value);
				break;
			case 2:
				sizeList = myList.size();
				cout << "The size of your list is: " << sizeList << endl; // returning size to user
				break;
			case 3:
				myList.display();
				break;
			case 4:
				myList.reverse();
				break;
			case 5:
		        cout << "Heres the list you made: " <<  endl;

		        myList.display();

		        cout << "Enter the index values of the two adjacent positions you want to swap, smallest first: " << endl;
		        cout << "Index 1: " << endl;
		        cin >> index1;
		        cout << "Index 2: " << endl;
		        cin >> index2;

		        sizeList = myList.size();

		        whatHappen = myList.swapElements(index1,index2,sizeList);

		        if(whatHappen == -1)
		        {
		        	return 0;
		        }
		        else
		        {

		        cout << "Heres your new list" << endl;

		        myList.display();

		        cout << "Program ending" << endl;

		        return 0;
		        }
			case 6:
				cout << "Program ended" << endl;
				return 0; // ending the program
			default:
				cout << "Wrong input choice, try again!" << endl;
				break;
			}
        }

        return 0; // a fail safe in case we somehow get out of the while loop
}

void linkedList::newNode(int value)
{

        struct node *spot, *holder; //creating two structures
        holder = new(struct node); // allocating the space for new node
        holder->number = value; // assigning it the number as specified by user
        holder->next = NULL;
        if (start == NULL)
        {
            holder->behind = NULL;// because it will be first element in we just put -> behind to NULL
            start = holder;
        }
        else
        {
            spot = start;
            while (spot->next != NULL) // go one away from the end
            {
                spot = spot->next;
            }
            spot->next = holder; // add your element at the end
            holder->behind = spot; // make sure behind points to one away from the end
        }
}


void linkedList::add(int value)
{

        struct node *holder; // the new node
        holder = new (struct node); // allocating space in memory for it
        holder->behind = NULL; // adding at the beginning so behind it will be NULL
        holder->number = value; //user specified value
        holder->next = start;
        start->behind = holder;
        start = holder; // we are at start so now start must point to this

}
void linkedList::display()
{
    struct node *holder; // place holder
    if (start == NULL)
    {
        cout<<"Nothing in the list, can't display anything!"<<endl;
        return;
    }
    holder = start;
    cout<<"Your DLL is:"<<endl;
    while (holder != NULL) // go through every element in the list
    {
        cout<<holder->number<<" <-> "; // display the number in each node
        holder = holder->next; // move to the next node
    }
    cout<<"NULL"<<endl;
}

int linkedList::size(){
	struct node *list; // initialization of the node structure
	int count; // our counter
    list = start; // starting at the beginning
	count = 0;
    while (list != NULL)  // till we reach the end
    {
        list = list->next; // next node
        count++;
    }
    return count; //return list size
}



void linkedList::reverse()
{
    struct node *normal, *ahead; //creating two variables normal and ahead, normal will always be one ahead of normal
    normal = start;
    ahead = normal->next; // placing ahead one in front of normal
    normal->next = NULL; //first element starts to become the last by pointing forward at NULL
    normal->behind = ahead; // and pointing to the one ahead as the one behind
    while (ahead != NULL)
    {
        ahead->behind = ahead->next;  // moving "ahead" forward one node
        ahead->next = normal;
        normal = ahead;
        ahead = ahead->behind;
    }
    start = normal;
}

int linkedList::swapElements(int index1, int index2, int sizeList)
{
	struct node *stop1, *stop2, *stop3,*stop4; // initialization of the node structure
	    stop1 = start; // starting at the beginning
	    stop2 = start; //This is so we can get to the appropriate spot in our list using for loops
	    stop3 = start;
	    stop4 = start;
	    if(index1 != 1 && index2 != sizeList && index1 < sizeList && index2 <= sizeList)
	    {

			for(int i = 1; i < index1-1; i++)
			{
				stop1 = stop1->next; //one node before smallest index
			}
			for(int i = 1; i < index1; i++)
			{
				stop2 = stop2->next; // smallest index we want to swap
			}
			for(int i = 1; i < index2; i++)
			{
				stop3 = stop3->next; // biggest index we want to swap
			}
			for(int i = 1; i < index2+1; i++)
			{
				stop4 = stop4->next; // one node after biggest one
			}
			stop3->next = stop2; //the swapping of the bigger index value now points to the smaller index value
			stop3->behind = stop1; //Making sure appropriate value is behind
			stop2->next = stop4; // the swapping of the smaller one now points to the bigger index value + 1
			stop2->behind = stop3;//Making sure appropriate value is behind
			stop1->next = stop3; // the (smaller index value - 1) now points to the third index value
	    }
	    else if(index1 == 1)
	    {

	    	stop2 = stop1->next; // second element
	        stop3 = stop2->next; // third element

	        stop1->next = stop3; //Now the first element points to the third element
	        stop1->behind = stop2; //the first element is now ahead of second element so it points back to it
	        stop2->behind = NULL; // behind the first element is nothing
	        stop3->behind = stop1; //the element behind the third element is now the first element
	        stop2->next = stop1; //now the second element points to the first
	        start = stop2; // The new start is the second element

	    }
	    else if (index1 == sizeList-1 && index2 == sizeList)
	    {
			for(int i = 1; i < index1-1; i++)
			{
				stop1 = stop1->next; //one node before smallest index
			}
			for(int i = 1; i < index1; i++)
			{
				stop2 = stop2->next; // smallest index we want to swap
			}
			for(int i = 1; i < index2; i++)
			{
				stop3 = stop3->next; // biggest index we want to swap
			}
			stop1->next = stop3; //the one before the first index value points to the last element
			stop2->next = NULL; // the first index value now points to NULL (set to the end)
			stop2->behind = stop3; //the final element is the second last one and now must point behind to the old final element
			stop3->next = stop2; // the biggest index value now points to the smallest index value
			stop3->behind = stop1;
	    }
	    else
	    {
	    	cout<< "Out of index range! Not able to swap!" << endl;
	    	return -1;
	    }

return 0;
}

