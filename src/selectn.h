/*
 *	selectn.h
 *	Selection stuff
 *	AYM 1998-10-23
 */


#ifndef YH_SELECTN
#define YH_SELECTN

class bitvec_c;


/* The selection list is used when more than one object is selected. */
typedef struct SelectionList *SelPtr;
struct SelectionList
   {
   SelPtr next;			/* next in list */
   int objnum;			/* object number */
   };

bool IsSelected (SelPtr, int);
void DumpSelection (SelPtr list);
void SelectObject (SelPtr *, int);
void select_unselect_obj (SelPtr *list, int objnum);
void UnSelectObject (SelPtr *, int);
void ForgetSelection (SelPtr *);
bitvec_c *list_to_bitvec (SelPtr list, size_t bitvec_size);
SelPtr bitvec_to_list (const bitvec_c &b);

#endif

