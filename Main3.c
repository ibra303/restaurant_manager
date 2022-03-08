#include "Header3.h"
// main func
int main()
{
	int Tables, Input, Q, TN, i = 0;
	char name[50];
	t* temp;
	mange ptr8;
	FILE* IN = fopen("Instructions.txt", "r");
	FILE* out = fopen("output file.txt", "w");
	if (!out)
	{
		printf("Cannot open file!");
		exit(1);
	}
	if (!IN)
	{
		printf("Cannot allocate memory!");
		exit(1);
	}
	fscanf(IN, "%d", &Tables);
	// malloc to open tables
	temp = (t*)malloc(Tables * sizeof(t));
	if (!temp)
	{
		printf("Cannot allocate memory!");
		exit(1);
	}
	for (i = 0; i < Tables; i++)
	{
		temp[i].order = 0;
		temp[i].bill = 0;
		temp[i].tmp = NULL;
	}
	// while the file is not end
	while (fscanf(IN, "%d", &Input) > 0)
	{
		if (Input == 1)
		{
			CreateProduct(&ptr8, out, &temp, Tables);
			fprintf(out, "The kitchen was created\n");
		}
		if (Input == 2)
		{
			fscanf(IN, "%s %d", name, &Q);
			AddItems(&ptr8, name, Q, out);
		}
		if (Input == 3)
		{
			fscanf(IN, " %d %s %d", &TN, name, &Q);
			OrderItem(&ptr8, &temp, TN, name, Q, Tables, out);
		}
		if (Input == 4)
		{
			fscanf(IN, "%d%s%d", &TN, name, &Q);
			RemoveItem(&temp, &ptr8, TN, name, Q, Tables, out);
		}
		if (Input == 5)
		{
			fscanf(IN, "%d", &TN);
			RemoveTable(&temp, TN, Tables, &ptr8, out);
		}
	}
	deletelinkedlist(&ptr8);
	deletetablesinkedlists(&temp, Tables);
	fclose(IN);
	fclose(out);
	return 0;
}

