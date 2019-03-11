#include <stdio.h>
#include <stdlib.h>
#include "genericlist.h"


GLIST * insertNode(GLIST *list, void *data)
{
	GLIST *node = NULL, *iter = NULL, *temp = NULL;
	node = malloc (sizeof(GLIST));
	node->data = data;
	node->next = NULL;
	node->action_callback = node->debug_callback = NULL;
	if (list == NULL)
		return node;
	else
	{
		/* Insert at the end */
		iter = list;
		while (iter)
		{
			temp = iter;
			iter = iter->next;
		}
		temp->next = node;
	}
	return list;
}

GLIST * removeNode(GLIST *list, void *data)
{
	GLIST *iter = list;
	GLIST *temp = NULL;

	if (list == NULL)
		return list;

	/* first node */
	if (list->data == data)
	{
		temp = list;
		list = list->next;
		free(temp);
		temp = NULL;
		return list;
	}

	iter = temp = list;
	while (iter)
	{
		if (iter->data == data)
		{
			temp->next = iter->next;
			free(iter);
			iter = NULL;
			return list;
		}
		temp = iter;
		iter = iter->next;
	}
	printf ("list element not found\n");
	return list;
}

void showElem(GLIST *list)
{
	int i = 0;
	GLIST *temp = list;
	for (; temp; temp = temp->next)
	{
		printf ("Elem #%-3d     DataPtr %p\n", i++, temp->data);
	}
}

GLIST * removeAllNodes(GLIST *list)
{
	GLIST * temp, *iter;
	for (iter = list; iter;)
	{
		temp = iter;
		iter = iter->next;
		free (temp);
		temp = NULL;
	}
	return NULL;
}

void gListInit(LIST *list, const char *listname)
{
	if (list == NULL)
		return;
	else if (list->list != NULL && list->num_node != 0)
	{
		printf("%s: List is not enpty\n", __FUNCTION__);
		return;
	}

	list->list = NULL;
	list->num_node = 0;
	list->add_callback = NULL;
	list->del_callback = NULL;
	list->show_callback = NULL;
	list->usr_callback = NULL;
	snprintf(list->list_name, GLIST_NAME_STR_LEN, "%s", listname);
}

void gListAddCallbak(LIST *list, LIST_CALLBACK_TYPE type, void (*callback) (void *))
{
	if (list == NULL)
		return;

	switch (type)
	{
		case CALLABCK_TYPE_ALL:
			list->add_callback =
			list->del_callback = 
			list->show_callback =
			list->usr_callback = callback;
		break;
		case CALLABCK_TYPE_ADD:
			list->add_callback = callback;
		break;
		case CALLABCK_TYPE_DEL:
			list->del_callback = callback;
		break;
		case CALLABCK_TYPE_SHOW:
			list->show_callback = callback;
		break;
		case CALLABCK_TYPE_USR:
			list->usr_callback = callback;
		break;
		case CALLABCK_TYPE_ACT:
		break;
		case CALLABCK_TYPE_DBG:
		break;
		default :
		break;
		
	}
}

void gListRemoveCallbak(LIST *list, LIST_CALLBACK_TYPE type)
{
	if (list == NULL)
		return;

	switch (type)
	{
		case CALLABCK_TYPE_ALL:
			list->add_callback =
			list->del_callback = 
			list->show_callback =
			list->usr_callback = NULL;
		break;
		case CALLABCK_TYPE_ADD:
			list->add_callback = NULL;
		break;
		case CALLABCK_TYPE_DEL:
			list->del_callback = NULL;
		break;
		case CALLABCK_TYPE_SHOW:
			list->show_callback = NULL;
		break;
		case CALLABCK_TYPE_USR:
			list->usr_callback = NULL;
		break;
		case CALLABCK_TYPE_ACT:
		break;
		case CALLABCK_TYPE_DBG:
		break;
		default :
		break;
		
	}
}

void gListShow(LIST *list)
{
	if (list == NULL)
		return;
	printf ("List Name        : %s\n", list->list_name);
	printf ("List Elem        : %d\n", list->num_node);
	printf ("List Callback(A) : %s\n", (list->add_callback)  ? "Present" : "Un Initilized");
	printf ("List Callback(D) : %s\n", (list->del_callback)  ? "Present" : "Un Initilized");
	printf ("List Callback(S) : %s\n", (list->show_callback) ? "Present" : "Un Initilized");
	printf ("List Callback(U) : %s\n", (list->usr_callback)  ? "Present" : "Un Initilized");

	if (list->show_callback != NULL)
		list->show_callback(list);
	else
	{
		printf ("List Element\n------------------------------------------------------------\n");
		showElem(list->list);
	}
}

void gListAddElem(LIST *list, void *data)
{
	list->list = insertNode(list->list, data);
	list->num_node++;
	if (list->add_callback)
		list->add_callback(data);
}

void gListPreAddElem(LIST *list, void *data)
{
	GLIST *node = NULL;
	node = malloc (sizeof(GLIST));
	node->data = data;

	node->next = list->list;
	list->list = node;

	list->num_node++;
	if (list->add_callback)
		list->add_callback(data);
}

void gListRemoveElem(LIST *list, void *data)
{
	list->list = removeNode(list->list, data);
	list->num_node--;
	if (list->del_callback)
		list->del_callback(data);
}

void gListDestroy(LIST *list)
{
	if (list == NULL)
		return;
	list->list = removeAllNodes(list->list);
	list->num_node = 0;
	list->add_callback = NULL;
	list->del_callback = NULL;
	list->show_callback = NULL;
	list->usr_callback = NULL;
}

void * gLiistIterInit(LIST *list, GLITER *iter)
{
	iter->prev_node = NULL;
	iter->cur_node = list->list;
	if (iter->cur_node)
		iter->next_node = iter->cur_node->next;
	iter->iter_init = ITER_INITIALIZED;
	return iter->cur_node->data;
}

void * gLiistIterFirst(LIST *list, GLITER *iter)
{
	return gLiistIterInit(list, iter);
}

void * gLiistIterNext(LIST *list, GLITER *iter)
{
	if (list == NULL || iter == NULL)
	{
		return NULL;
	}
	if (iter->iter_init == ITER_UNINITIALIZED)
	{
		printf("%s: Iter is not Initialized\n", __FUNCTION__);
		return NULL;
	}

	if (iter->cur_node == NULL)
	{
		if (iter->prev_node != NULL)
		{
			iter->cur_node = iter->prev_node->next;
		} 
		else
		{
			iter->cur_node = list->list;
		}

		if (iter->cur_node)
		{
			iter->next_node = iter->cur_node->next;
			return iter->cur_node->data;
		}
		else
			return NULL;
	}

	/* check if next node exist */
	if (iter->cur_node->next == NULL)
	{
		iter->prev_node = iter->cur_node;
		iter->next_node = NULL;
		return NULL;
	}
	/* move all pointers */
	else
	{
		iter->prev_node = iter->cur_node;
		iter->cur_node = iter->cur_node->next;
		iter->next_node = iter->cur_node->next;
	}
	return iter->cur_node->data;
}

void gLiistIterRemove(LIST *list, GLITER *iter)
{
	GLIST *temp = NULL;
	temp = iter->cur_node;

	if (list == NULL || iter == NULL)
	{
		return;
	}
	if (iter->iter_init == ITER_UNINITIALIZED)
	{
		printf("%s: Iter is not Initialized\n", __FUNCTION__);
		return;
	}

	if (iter->prev_node == NULL)
	{
		if (iter->cur_node)
		{
			iter->cur_node = iter->cur_node->next;
			if (iter->cur_node)
				iter->next_node = iter->cur_node->next;
		}
		list->list = iter->cur_node->next;
	}
	else
	{
		if (iter->cur_node)
		{
			iter->cur_node = iter->cur_node->next;
			iter->prev_node->next = iter->cur_node;
			if (iter->cur_node)
				iter->next_node = iter->cur_node->next;
		}
	}
	if(temp){
		list->num_node--;
		free(temp);
	}
	iter->cur_node = NULL;
}
