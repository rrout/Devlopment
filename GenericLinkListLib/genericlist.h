#include <stdio.h>
#include <stdlib.h>


#ifndef __GENERIC_LIST_H__
#define __GENERIC_LIST_H__
typedef struct _list{
	void *data;
	void (*action_callback) (void *arg);
	void (*debug_callback) (void *arg);
	struct _list *next;
}GLIST;

#define GLIST_NAME_STR_LEN 65
typedef enum {
	CALLABCK_TYPE_ALL,
	CALLABCK_TYPE_ADD,
	CALLABCK_TYPE_DEL,
	CALLABCK_TYPE_SHOW,
	CALLABCK_TYPE_USR,
	CALLABCK_TYPE_ACT,
	CALLABCK_TYPE_DBG
}LIST_CALLBACK_TYPE;

typedef struct _glist{
	GLIST	*list;
	char	list_name[GLIST_NAME_STR_LEN];
	int		num_node;
	void	(*add_callback) (void *arg);
	void	(*del_callback) (void *arg);
	void	(*show_callback) (void *arg);
	void	(*usr_callback) (void *arg);
}LIST;

typedef enum {
	ITER_UNINITIALIZED,
	ITER_INITIALIZED
}ITER_STATUS;

typedef struct _giter{
	int iter_init;
	GLIST *prev_node;
	GLIST *cur_node;
	GLIST *next_node;
}GLITER;

GLIST * insertNode(GLIST *list, void *data);
GLIST * removeNode(GLIST *list, void *data);
void showElem(GLIST *list);
GLIST * removeAllNodes(GLIST *list);


void gListInit(LIST *list, const char *listname);
void gListAddCallbak(LIST *list, LIST_CALLBACK_TYPE type, void (*callback) (void *));
void gListRemoveCallbak(LIST *list, LIST_CALLBACK_TYPE type);
void gListShow(LIST *list);
void gListAddElem(LIST *list, void *data);
void gListPreAddElem(LIST *list, void *data);
void gListRemoveElem(LIST *list, void *data);
void gListAppend(LIST *list, void *data);
void gListPrepend(LIST *list, void *data);
void gListDestroy(LIST *list);

void * gLiistIterInit(LIST *list,GLITER *iter);
void * gLiistIterNext(LIST *list, GLITER *iter);
void gLiistIterRemove(LIST *list, GLITER *iter);


#endif /*__GENERIC_LIST_H__*/
