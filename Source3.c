#include "Header3.h"

// function name : CreateProduct //
// input : head of null linked list and output file //
// output : arrange the food in the kitchen //
// algorithim : two while loops and for loop //
void CreateProduct(m s, FILE* out, t** ptr9, int tables)
{
	int price1, quantity1, namelength, i = 0, namelength1, namelength2, j, false1 = FALSE, true1 = TRUE;
	char name[50];
	ps tmp5;
	FILE* in;
	m p;
	s->head = NULL;
	s->tail = NULL;
	in = fopen("Manot.txt", "r");
	if (!in)
	{
		printf("Cannot open Manot file!");
		deletetablesinkedlists(ptr9, tables);
		exit(1);
	}
	while (fscanf(in, "%s%d%d", name, &quantity1, &price1) != EOF)
	{
		p = s->head;
		namelength2 = strlen(name);
		while (s->head && false1 == FALSE)
		{
			namelength1 = strlen(s->head->mealname);
			if (namelength2 == namelength1)
			{
				for (j = 0; j < namelength1; j++)
				{
					if (name[j] != s->head->mealname[j])
					{
						true1 = FALSE;
						j = namelength1;
					}
				}
				if (true1 == TRUE)
					false1 = TRUE;
			}
			true1 = TRUE;
			s->head = s->head->next;
		}
		s->head = p;
		if (false1 == TRUE)
		{
			fprintf(out, "This meal is already existed\n");
			false1 = FALSE;
		}
		else
		{
			if (price1 < 0 && quantity1 < 0)
				fprintf(out, "The price and the quantity cannot be negative!\n");
			if (price1 < 0 && quantity1 >= 0)
				fprintf(out, "Price cannot be negative!\n");
			if (quantity1 < 0 && price1 >= 0)
				fprintf(out, "Quantity cannot be negative!\n");
			if (price1 > 0 && quantity1 > 0)
			{
				tmp5 = (products*)malloc(1 * sizeof(products));
				if (!tmp5)
				{
					printf("Cannot allocate memory!");
					deletetablesinkedlists(ptr9, tables);
					exit(1);
				}
				namelength = strlen(name);
				tmp5->mealname = (char*)malloc((namelength + 1) * sizeof(char));
				if (!tmp5->mealname)
				{
					printf("Cannot allocate memory!");
					deletelinkedlist(&s);
					deletetablesinkedlists(ptr9, tables);
					exit(1);
				}
				strcpy(tmp5->mealname, name);
				tmp5->mealprice = price1;
				tmp5->quantity = quantity1;
				tmp5->numoforder = 0;
				tmp5->next = NULL;
				if (s->head == NULL)
					s->head = tmp5;
				else
					s->tail->next = tmp5;
				s->tail = tmp5;
			}
		}
	}
	fclose(in);
}
// function name : AddItems //
// input : pointer to the linked list food in kitchen and the product name and the quantity to add and the output file //
// output : add the items to the kitchen //
// algorithim : while and for loops //
void AddItems(m meals, char* productname, int quantity, FILE* out)
{
	ps* ptr, * temp = 0;
	ptr = meals->head;
	int namelength1, namelength2, i, true1 = FALSE, false1 = TRUE;
	if (quantity < 0)
	{
		fprintf(out, "The amount of items cannot be negative!\n");
	}
	else
	{
		while (meals->head && true1 == FALSE)
		{
			namelength1 = strlen(meals->head->mealname);
			namelength2 = strlen(productname);
			if (namelength1 == namelength2)
			{
				for (i = 0; i < namelength1; i++)
				{
					if (meals->head->mealname[i] != productname[i])
					{
						i = namelength1;
						false1 = FALSE;
					}
				}
				if (false1 == TRUE)
				{
					true1 = TRUE;
					temp = meals->head;
				}
			}
			meals->head = meals->head->next;
		}
		meals->head = temp;
		if (true1 == FALSE)
		{
			fprintf(out, "This meal does not exist\n");
		}
		if (true1 == TRUE)
		{
			meals->head->quantity += quantity;
			fprintf(out, "%d %s were added to the kitchen\n", quantity, productname);
		}
		meals->head = ptr;
	}
} // function name : OrderItem //
 // input : head of food linked list,pointer to the tables array, tables number, the meal name, the quantity, table number,output file //
 // output : submit the customers orders and manage the kitchen according to the orders //
// algorithim : two while loops and two for loops //
void OrderItem(m meals, t** ptr, int tablenum, char* productname, int quantity, int tables, FILE* out)
{
	ps* ptr1;
	pot* temp, * temp1;
	pot1 tmp5 = 0, tmp6 = 0;
	products* ptr2 = 0;
	temp1 = (*ptr)[tablenum - 1].tmp;
	ptr1 = meals->head;
	int namelength1, namelength2, i, true1 = FALSE, namelength3, j = 1, false1 = FALSE;
	(*ptr)[tablenum - 1].order = 1;
	namelength2 = strlen(productname);
	while (false1 == FALSE && (*ptr)[tablenum - 1].tmp)
	{
		tmp5 = (*ptr)[tablenum - 1].tmp;
		namelength1 = strlen((*ptr)[tablenum - 1].tmp->meal);
		if (namelength1 == namelength2)
		{
			for (i = 0; i < namelength1; i++)
			{
				if ((*ptr)[tablenum - 1].tmp->meal[i] != productname[i])
				{
					false1 = TRUE;
					i = namelength1;
				}
			}
			if (false1 == FALSE)
			{
				false1 = TRUE;
				tmp6 = (*ptr)[tablenum - 1].tmp;
				j = 0;
			}
			else
				false1 = FALSE;
		}
		(*ptr)[tablenum - 1].tmp = (*ptr)[tablenum - 1].tmp->prev;
	}
	(*ptr)[tablenum - 1].tmp = temp1;
	while (meals->head != NULL && true1 == FALSE)
	{
		namelength1 = strlen(meals->head->mealname);
		namelength2 = strlen(productname);
		if (namelength1 == namelength2)
		{
			for (i = 0; i < namelength1; i++)
			{
				if (meals->head->mealname[i] != productname[i])
				{
					i = namelength1;
					true1 = TRUE;
				}
			}
			if (true1 == FALSE)
			{
				true1 = TRUE;
				ptr2 = meals->head;
			}
			else
				true1 = FALSE;
		}
		meals->head = meals->head->next;
	}
	if (true1 == FALSE)
		fprintf(out, "We don't have %s, sorry!\n ", productname);
	if (tablenum > tables)
		fprintf(out, " This table is not existed tables number is %d \n", tables);
	else
		if (quantity < 0)
			fprintf(out, "The amount of orders cannot be negative!\n");
		else
		{
			if (true1 == TRUE && j == 1)
			{
				temp = (pot*)malloc(sizeof(pot));
				if (!temp)
				{
					printf("Cannot allocate memory!");
					deletelinkedlist(&meals);
					deletetablesinkedlists(ptr, tables);
					exit(1);
				}
				meals->head = ptr2;
				namelength3 = strlen(meals->head->mealname);
				temp->meal = (char*)malloc((namelength3 + 1) * sizeof(char));
				if (!(temp->meal))
				{
					printf("Cannot allocate memory!");
					deletelinkedlist(&meals);
					deletetablesinkedlists(ptr, tables);
					exit(1);
				}
				strcpy(temp->meal, meals->head->mealname);
				temp->mealprice = ptr2->mealprice;
				temp->quantity = quantity;
				ptr2->quantity = ptr2->quantity - quantity;
				ptr2->numoforder += quantity;
				temp->next = NULL;
				if ((*ptr)[tablenum - 1].tmp == NULL)
				{
					temp->prev = NULL;
					temp->next = NULL;
					(*ptr)[tablenum - 1].tmp = temp;
					(*ptr)[tablenum - 1].bill = (*ptr)[tablenum - 1].bill + (quantity * (*ptr)[tablenum - 1].tmp->mealprice);
					fprintf(out, "%d %s were added to table number %d\n", quantity, productname, tablenum);
				}
				else
				{
					(*ptr)[tablenum - 1].bill = (*ptr)[tablenum - 1].bill + (temp->quantity * temp->mealprice);
					(*ptr)[tablenum - 1].tmp->next = temp;
					temp->prev = (*ptr)[tablenum - 1].tmp;
					(*ptr)[tablenum - 1].tmp = temp;
					fprintf(out, "%d %s were added to table number %d\n", quantity, (*ptr)[tablenum - 1].tmp->meal, tablenum);
				}
			}
			if (j == 0)
			{
				tmp6->quantity += quantity;
				ptr2->quantity = ptr2->quantity - quantity;
				ptr2->numoforder += quantity;
				fprintf(out, "%d %s were added to table number %d\n", quantity, productname, tablenum);
				(*ptr)[tablenum - 1].bill = (*ptr)[tablenum - 1].bill + (quantity * tmp6->mealprice);
				(*ptr)[tablenum - 1].tmp = temp1;
			}
		}
	meals->head = ptr1;
}
// function name : RemoveItem //
// input : pointer pf the tables array, head of food linked list, table number, the meal name, the quantity, number of tables, output file //
// output : remove items from specific table if the customer want and change the bill //
// algorithim : two while loops and two for loops //
void RemoveItem(t** table, m ptr, int tablenum, char* productname, int quantity, int tables, FILE* out)
{
	m ptr1;
	ptr1 = ptr->head;
	pot* tmp2 = 0, * tmp4 = 0, * tmp3 = 0;
	tmp3 = (*table)[tablenum - 1].tmp;
	int namelength1, namelength2, i, false1 = FALSE, namelength3, true1 = 0;
	namelength1 = strlen(productname);
	while (ptr->head && true1 == 0)
	{
		namelength3 = strlen(ptr->head->mealname);
		if (namelength3 == namelength1)
		{
			for (i = 0; i < namelength1; i++)
			{
				if (ptr->head->mealname[i] != productname[i])
				{
					true1 = 1;
					i = namelength1;
				}
			}
			if (true1 == 0)
				true1 = 1;
			else
				true1 = 0;
		}
		ptr->head = ptr->head->next;
	}
	ptr->head = ptr1;
	if (true1 == 0)
		fprintf(out, "There is no %s in the resturant! \n", productname);
	if (quantity < 0)
		fprintf(out, "The amount of order cannot be negative! \n");
	if (tablenum > tables)
		fprintf(out, "This table is not existed tables number is %d \n", tables);
	if (true1 == 1)
	{
		while (false1 == FALSE && (*table)[tablenum - 1].tmp)
		{
			namelength2 = strlen((*table)[tablenum - 1].tmp->meal);
			if (namelength1 == namelength2)
			{
				for (i = 0; i < namelength1; i++)
				{
					if ((*table)[tablenum - 1].tmp->meal[i] != productname[i])
					{
						i = namelength1;
						true1 = FALSE;
					}
				}
				if (true1 == TRUE)
				{
					false1 = TRUE;
					tmp2 = (*table)[tablenum - 1].tmp;
				}
			}
			(*table)[tablenum - 1].tmp = (*table)[tablenum - 1].tmp->prev;
		}
		if (false1 == FALSE && tmp3 != NULL)
			fprintf(out, "Table number %d did not orderd this meal\n", tablenum);
		else
			if (false1 == FALSE && tmp3 == NULL)
				fprintf(out, "Table number %d did not ordered yet! \n", tablenum);
			else
			{
				tmp2->quantity = tmp2->quantity - quantity;
				(*table)[tablenum - 1].bill = (*table)[tablenum - 1].bill - (tmp2->mealprice * quantity);
				fprintf(out, "%d %s was returned to the kitchen from table number %d\n", quantity, productname, tablenum);
			}
		(*table)[tablenum - 1].tmp = tmp3;
	}
}
// function name : RemoveTable //
// input : pointer of tables array, table num, number of tables in the resturant, head of food linked list, output file //
// output : close the table and give the customer the bill and if the table was the last prints the most asked meal in the day //
// algorithim : two while loops and for loop //
void RemoveTable(t** ptr, int tablenum, int tables, m ptr5, FILE* out)
{
	int i = 0, count = 0;
	products* temp = 0, * temp1;
	temp1 = ptr5->head;
	pot* tmp3, * tmp4;
	tmp3 = (*ptr)[tablenum - 1].tmp;
	if ((*ptr)[tablenum - 1].tmp == NULL)
		fprintf(out, "The table number %d is not ordered yet\n", tablenum);
	else
	{
		while ((*ptr)[tablenum - 1].tmp != NULL)
		{
			if ((*ptr)[tablenum - 1].tmp->quantity > 0)
				fprintf(out, "%d %s", (*ptr)[tablenum - 1].tmp->quantity, (*ptr)[tablenum - 1].tmp->meal);
			if ((*ptr)[tablenum - 1].tmp->prev != NULL && (*ptr)[tablenum - 1].tmp->quantity > 0)
				fprintf(out, ", ");
			(*ptr)[tablenum - 1].tmp = (*ptr)[tablenum - 1].tmp->prev;
		}
		(*ptr)[tablenum - 1].tmp = tmp3;
		fprintf(out, ". %d nis,Please!\n", (*ptr)[tablenum - 1].bill);
		if ((*ptr)[tablenum].order == 0)
		{
			while (ptr5->head)
			{
				if (count < ptr5->head->numoforder)
				{
					count = ptr5->head->numoforder;
					temp = ptr5->head;
				}
				ptr5->head = ptr5->head->next;
			}
			fprintf(out, "The most popular dish today is %s! (was orderd %d times)\n", temp->mealname, count);
		}
	}
	ptr5->head = temp1;
}
// 
void deletelinkedlist(m k)
{
	products* tmp;
	int i = 0;
	while (k->head)
	{
		tmp = k->head;
		k->head = k->head->next;
		free(tmp->mealname);
		free(tmp);
	}
}
void deletetablesinkedlists(t** ptr, int tables)
{
	pot* tmp4;
	int i;
	for (i = 0; i < tables; i++)
	{
		while ((*ptr)[i].tmp)
		{
			tmp4 = (*ptr)[i].tmp;
			(*ptr)[i].tmp = (*ptr)[i].tmp->prev;
			free(tmp4->meal);
			free(tmp4);
		}
	}
	free(*ptr);
}

