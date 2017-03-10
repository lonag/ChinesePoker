/*
 *侵入式的单向列表
*/
#ifndef _LLIST_H
#define _LLIST_H

#include <stdint.h>
#include <stdlib.h>

struct lnode
{
    lnode *next;
};


struct llist
{
private:
	int   size;
    lnode *head;
    lnode *tail;
public:
	llist():size(0),head(NULL),tail(NULL){
	}

	lnode *Head(){
		return head;
	}

	lnode *Tail(){
		return tail;
	}

	void push_back(lnode *node){
		if(node->next) return;
		node->next = NULL;
		if(0 == size)
			head = tail = node;
		else
		{
			tail->next = node;
			tail = node;
		}
		++size;
	}


	void push_front(lnode *node)
	{
		if(node->next) return;
		node->next = NULL;
		if(0 == size)
			head = tail = node;
		else
		{
			node->next = head;
			head = node;
		}
		++size;
	}

	lnode* llist_pop()
	{
		if(0 == size)
			return NULL;
		lnode *node = head;
		head = head->next;
		if(NULL == head)
			tail = NULL;
		--size;
		node->next = NULL;
		return node;
	}

	bool isEmpty(){
		return size == 0;
	}

	int Size(){
		return size;
	}
};

#endif
