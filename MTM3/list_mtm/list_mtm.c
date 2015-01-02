#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../list_mtm1.h"

//**************** MACRO ******************************************************
#define NULL_ARG(arg, returnVal) if(arg == NULL) { \
													return returnVal; \
												}

#define CHECK_ARG(arg, val, returnVal) if(arg == val) { \
													return returnVal; \
												}

//***********************************  STRUCTS  ******************************
typedef struct node {
	ListElement element;
	struct node* next;

}*Node;


struct List_t {
	Node head;
	Node current;
	CopyListElement copyElement;
	FreeListElement freeElement;
};

//*************************************************************************


List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	NULL_ARG(copyElement, NULL)
	NULL_ARG(freeElement, NULL)
	List newList = malloc(sizeof(*newList));
	NULL_ARG(newList, NULL)
	newList->head = NULL;
	newList->current = NULL; //undefined
	newList->copyElement = copyElement;
	newList->freeElement = freeElement;
	return newList;
}

//*************************************************************************

ListResult listInsertLast(List list, ListElement element) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(element, LIST_NULL_ARGUMENT)
	ListElement elemCopy = list->copyElement(element);
	NULL_ARG(elemCopy, LIST_OUT_OF_MEMORY)
	Node newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		list->freeElement(elemCopy);
		return LIST_OUT_OF_MEMORY;
	}
	newNode->element = elemCopy;
	newNode->next = NULL;
	Node ptr = list->head;
	if (ptr != NULL) {
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = newNode;
	} else {
		list->head = newNode;
	}
	return LIST_SUCCESS;

}

//*************************************************************************

ListResult listInsertFirst(List list, ListElement element) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(element, LIST_NULL_ARGUMENT)
	ListElement elemCopy = list->copyElement(element);
	NULL_ARG(elemCopy, LIST_NULL_ARGUMENT)
	Node newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		list->freeElement(elemCopy);
		return LIST_OUT_OF_MEMORY;
	}
	newNode->next = list->head;
	newNode->element = elemCopy;
	list->head = newNode;
	return LIST_SUCCESS;
}

//*************************************************************************

ListResult listInsertBeforeCurrent(List list, ListElement element) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(list->current, LIST_INVALID_CURRENT)
	ListElement newElement = list->copyElement(element);
	NULL_ARG(newElement, LIST_OUT_OF_MEMORY)
	Node newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		list->freeElement(newElement);
		return LIST_OUT_OF_MEMORY;
	}
	newNode->element = newElement;
	newNode->next = list->current;
	Node ptr = list->head;
	while (ptr->next != list->current) {
		ptr = ptr->next;
	}
	ptr->next = newNode;
	return LIST_SUCCESS;
}

//*************************************************************************

ListElement listGetFirst(List list) {
	NULL_ARG(list, NULL)
	NULL_ARG(list->head, NULL)
	ListElement currentElement = list->head->element;
	list->current = list->head;
	return currentElement;
}

//*************************************************************************

ListElement listGetNext(List list) {
	NULL_ARG(list, NULL)
	NULL_ARG(list->head, NULL)
	if (list->current == NULL) {
		return NULL;
	}
	list->current = list->current->next;
	NULL_ARG(list->current, NULL)
	return list->current->element;
}

//*************************************************************************

int listGetSize(List list) {
	NULL_ARG(list, -1)
	CHECK_ARG(list->head, NULL, 0)
	Node ptr = list->head;
	int sizeCounter = 1;
	while (ptr->next) {
		ptr = ptr->next;
		sizeCounter++;
	}
	return sizeCounter;
}

//*************************************************************************

ListElement listGetCurrent(List list) {
	NULL_ARG(list, NULL)
	NULL_ARG(list->current, NULL)
	return list->current->element;
}

//*************************************************************************

ListResult listInsertAfterCurrent(List list, ListElement element) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(list->current, LIST_INVALID_CURRENT)
	ListElement newElement = list->copyElement(element);
	NULL_ARG(newElement, LIST_OUT_OF_MEMORY)
	Node newNode = malloc(sizeof(*newNode));
	if (!newNode) {
		list->freeElement(newElement);
		return LIST_OUT_OF_MEMORY;
	}
	newNode->element = newElement;
	newNode->next = list->current->next;
	list->current->next = newNode;
	return LIST_SUCCESS;
}

//*************************************************************************

void listDestroy(List list) {
	if (!list) {
		return;
	}
	Node ptr = list->head;
	while (ptr != NULL) {
		ptr = ptr->next;
		list->freeElement(list->head->element);
		free(list->head);
		list->head = ptr;
	}
	free(list);
}

//*************************************************************************

List listCopy(List list) {
	NULL_ARG(list, NULL)
	List copiedList = listCreate(list->copyElement, list->freeElement);
	NULL_ARG(copiedList, NULL)
	Node ptrSrc = list->head;
	if (ptrSrc != NULL) {
		while (ptrSrc != NULL) {
			ListResult flag = listInsertLast(copiedList, ptrSrc->element);
			if (flag != LIST_SUCCESS) {
				listDestroy(copiedList);
				return NULL;
			}
			ptrSrc = ptrSrc->next;
		}
		if (list->current != NULL) {
			char* name = list->current->element;
			Node ptrDst = copiedList->head;
			while (ptrDst != NULL) {
				if (!strcmp(ptrDst->element, name)) {
					copiedList->current = ptrDst;
				}
				ptrDst = ptrDst->next;
			}
		}
	}
	return copiedList;
}

//*************************************************************************

List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
	NULL_ARG(list, NULL)
	NULL_ARG(filterElement, NULL)
	NULL_ARG(key, NULL)
	List filteredList = listCreate(list->copyElement, list->freeElement);
	NULL_ARG(filteredList, NULL)
	Node ptr = list->head;
	while (ptr->next != NULL) {
		bool isFiltered = filterElement(ptr->element, key);
		if (isFiltered) {
			ListResult flag = listInsertLast(filteredList, ptr->element);
			if (flag != LIST_SUCCESS) {
				listDestroy(filteredList);
				return NULL;
			}
		}
		ptr = ptr->next;
	}
	return filteredList;
}

//*************************************************************************

ListResult listRemoveCurrent(List list) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(list->current, LIST_INVALID_CURRENT)
	Node ptr = list->head;
	if (ptr == list->current) {
		list->head = ptr->next;
	} else {
		while (ptr->next != list->current) {
			ptr = ptr->next;
		}
		ptr->next = list->current->next;
	}
	list->freeElement(list->current->element);
	free(list->current);
	list->current = NULL;
	return LIST_SUCCESS;
}

//*************************************************************************

ListResult listClear(List list) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	Node ptr = list->head;
	while (ptr != NULL) {
		ptr = ptr->next;
		list->freeElement(list->head->element);
		free(list->head);
		list->head = ptr;
	}
	return LIST_SUCCESS;
}

//*************************************************************************

static void swap(List list, Node prev, Node curr, Node next) {
	if (!next) {
		return;
	}
	if (!prev) {
		list->head = next;
	} else {
		prev->next = next;
	}
	curr->next = next->next;
	next->next = curr;
}

ListResult listSort(List list, CompareListElements compareElement) {
	NULL_ARG(list, LIST_NULL_ARGUMENT)
	NULL_ARG(compareElement, LIST_NULL_ARGUMENT)
	int size = listGetSize(list);
	Node ptrCurr = NULL, ptrPrev = NULL;
	for (int i = 0; i < size - 1; i++) {
		int wasSwap = 0;
		ptrCurr = list->head;
		ptrPrev = NULL;
		for (int j = 0; j < size - 1; j++) {
			if (compareElement(ptrCurr->element, ptrCurr->next->element) > 0) {
				Node temp = ptrCurr->next;
				swap(list, ptrPrev, ptrCurr, ptrCurr->next);
				ptrPrev = temp;
				wasSwap = 1;
				continue;
			}
			ptrPrev = ptrCurr;
			ptrCurr = ptrCurr->next;
		}
		if (!wasSwap) {
			break;
		}
	}
	return LIST_SUCCESS;
}

