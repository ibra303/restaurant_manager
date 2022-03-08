#ifndef _Header
#define _Header
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
// this struct contain the food in the kitchen //
struct products
{
	char* mealname;
	int mealprice;
	int quantity;
	int numoforder;
	struct products* next;
}typedef products, * ps;
// this struct contain the food on the tables //
struct productsontable
{
	char* meal;
	int mealprice;
	int quantity;
	struct pot* next;
	struct pot* prev;
}typedef pot, * pot1;
// this struct contain the tables //
struct table
{
	int order;
	int bill;
	pot1 tmp;
}typedef t, * ta;
// this struct mange the food in the kitchen //
struct menahel
{
	struct products* head;
	struct products* tail;
}typedef mange, * m;
void CreateProduct(m s, FILE* out, t** ptr9, int tables);
void AddItems(m meals, char* productname, int quantity, FILE* out);
void OrderItem(m meals, t** ptr, int tablenum, char* productname, int quantity, int tables, FILE* out);
void RemoveItem(t** table, m ptr, int tablenum, char* productname, int quantity, int tables, FILE* out);
void RemoveTable(t** ptr, int tablenum, int tables, m ptr5, FILE* out);
void deletelinkedlist(m head);
void deletetablesinkedlists(t** temp, int tables);
#endif
