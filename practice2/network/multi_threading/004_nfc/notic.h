#include<stddef.h>
#include"utils.h"
#include "gluethread/glthread.h"

#define MAX_NOTIF_KEY_SIZE  64

//NFC is a linked list of callbacks(fp)
typedef struct notif_chain_{
	char nfc_name[64];
	glthread_t notif_chain_head; //head of linked list
}notif_chain_t;

typedef void (*nfc_app_cb)(void* , size_t);

typedef struct notif_chain_elem_{
	char key[MAX_NOTIF_KEY_SIZE];
	nfc_app_cb  app_cb;

	size_t key_size;
	bool_t is_key_set;
	glthread_t glue;
}notif_chain_elem_t;

/*when nfc invokes calllback func(nfce->app_cb())
 * to notify the subscriber, it should tell the subscriber about the type of update 
 * i.e, ADD,UPDATE,or DELETE.*/
typedef enum{
   NFC_UNKNOWN,
   NFC_ADD,
   NFC_MOD,
   NFC_DEL,
}nfc_op_t;



//subscription request 
void nfc_register_notif_chain(notif_chain_t *nfc,
		              notif_chain_elem_t *nfce);

//Invoke request when publisher wants to  post an  updates to subscribers 
void nfc_invoke_notif_chain(notif_chain_t *nfc,
                            void *arg,size_t argg_size,
	                    char *key,size_t key_size);




