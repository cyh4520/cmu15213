/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    //add by chen
    if(q!=NULL)
	{
    q->head = NULL;
	q->tail = NULL;
	q->size=0;
	}	
	//printf("%d",q->head->value);	
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{	
	if(q==NULL) return;
    /* How about freeing the list elementrs? */
    //add by chen
    list_ele_t *temp,*temp2;
	temp=q->head;
    while(temp)
    {
    //if the queue has next,then delete q and choose the next
	//first i write temp2=temp;free(temp);temp=temp2->next;that didnt work;
	//since when i alread free the temp,so this block is null,so temp2 is null alread
	//so you shoule flag the next first,then free.
	temp2=temp->next;
	free(temp);
	temp=temp2;
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
	//add by chen
	if (q==NULL)
	return false;
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
	//add by chen
	if(newh==NULL)
	return false;
    newh->value = v;
    newh->next = q->head;
	//add by chen
	if(q->head==NULL)
	q->tail=newh;

    q->head = newh;
	q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
	list_ele_t *newh;
	if(q==NULL)
	return false;
	newh=malloc(sizeof(list_ele_t));
	if(newh==NULL)
	return false;
    /* Remember: It should operate in O(1) time */
	newh->value=v;
	/*i missed add the newh->next=NULL,so there be always failed by queue has more than the queue's size's error,canse newh's next my point another block we dont know yet*/
	newh->next=NULL;
	if(q->head==NULL)
	q->head=newh;

	if(q->tail)
	q->tail->next=newh;
	q->tail=newh;
	q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
	if(q==NULL)
	return false;
	if(q->head==NULL)
	return false;
	if(vp!=NULL)
	*vp=q->head->value;
	list_ele_t *temp=q->head;
    q->head = q->head->next;
	//also i forget this if the q->head is null,i should get the tail to be null,too since we dont know where it will point
	if(q->head==NULL)
	q->tail=NULL;
	//and i forget the import thing!
	q->size--;
	free(temp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
	if(q==NULL)
	return 0;
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
	if(q==NULL) return;
	//miss next judgement
	if(q->head==NULL||q->tail==NULL) return;
	if(q->size==1) return;
	list_ele_t *p1,*p2,*p3;
	p1=q->head;
	p2=q->head;
	p1=p1->next;
	q->head->next=NULL;
	//O(n) that can be fast to avoid overtime
	while(p1)
	{
	//p2->next=NULL;
	p3=p1->next;
	p1->next=p2;
	p2=p1;
	p1=p3;
	}	
	p1=q->head;
	q->head=q->tail;
	q->tail=p1;

	/*time is O(n2) too bad will exceed
	list_ele_t *truetail=q->tail;
	list_ele_t *temp1,*temp2;
	temp1=q->head;
	temp2=q->head;
	while(q->head->next!=q->tail)
	{
		while(temp2->next!=q->tail)
		{
			temp1=temp2;
			temp2=temp2->next;
		}
		//this palce cant be q->tail it should be turetail->next
		//q->tail->next=temp2;
		truetail->next=temp2;
		//this place i ignored first. if i omit this code.the link will be bidrectional.
		temp2->next=NULL;

		temp1->next=q->tail;
		truetail=temp2;
		//when u complete all the functions,you forget to turn temp1 and temp2 back to head.
		//that will make mistake if the size more than 3.
		temp1=q->head;
		temp2=q->head;
	}
	truetail->next=q->head;
	//exchange head and tail
	truetail=q->head;
	q->head=q->tail;
	q->tail=truetail;
	//!!!forget this,because when reverse, the head go to the tail,and it point somewhere before,you shoule point it to NULL
	//emmsho u should always remember when you involve in the tail pointer,you should take care of the place where it point.always you should point it to NULL
	q->tail->next=NULL;
	printf("head: %d\n tail:%d\n",q->head->value,q->tail->value);*/
	
}

