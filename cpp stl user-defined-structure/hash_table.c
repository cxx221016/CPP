#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 16

typedef struct node
{
	char *key, *value;
	struct node *next;
} Node, *PNode, **PPNode;

PNode NewNode(const char *key, const char *value)
{
	PNode pNode = (PNode)malloc(sizeof(Node));
	pNode->next = NULL;
	if (key)
	{
		unsigned len = strlen(key) + 1;
		pNode->key = (char *)malloc(len);
		strcpy(pNode->key, key);
	}

	if (value)
	{
		unsigned len = strlen(value) + 1;
		pNode->value = (char *)malloc(len);
		strcpy(pNode->value, value);
	}
	return pNode;
}

void UpdateValue(PNode pNode, const char *value)
{
	if (pNode == NULL)
		return;
	if (value)
	{
		free(pNode->value);
		unsigned len = strlen(value) + 1;
		pNode->value = (char *)malloc(len);
		strcpy(pNode->value, value);
	}
}

typedef struct hash_table
{
	PPNode table;
	unsigned capacity;
	unsigned size;
} HashTable, *PHashTable;

PHashTable NewHashTable(unsigned capacity)
{
	if (capacity < 1)
		return NULL;
	PPNode pPNode = (PPNode)malloc(sizeof(PNode) * capacity);
	if (pPNode == NULL)
		return NULL;
	for (unsigned i = 0; i < capacity; ++i)
	{
		pPNode[i] = NULL;
	}

	PHashTable pHashTable = (PHashTable)malloc(sizeof(HashTable));
	if (pHashTable == NULL)
		return NULL;
	pHashTable->table = pPNode;
	pHashTable->capacity = capacity;
	pHashTable->size = 0;
	return pHashTable;
}

unsigned hash(const char *key, unsigned hashSize)
{
	unsigned int h = 0;
	for (; *key; ++key)
	{
		h = *key + h * 31;
	}
	return h % hashSize;
}

PNode findImpl(PHashTable pHashTable, const char *key)
{
	if (key == NULL)
		return NULL;
	unsigned idx = hash(key, pHashTable->capacity);
	PNode pNode = pHashTable->table[idx];
	if (pNode == NULL)
		return NULL;

	do
	{
		if (strcmp(pNode->key, key) == 0)
		{
			return pNode;
		}
		pNode = pNode->next;
	} while (pNode);
	return NULL;
}

const char *get(PHashTable pHashTable, const char *key)
{
	PNode pNode = findImpl(pHashTable, key);
	if (pNode == NULL)
		return NULL;
	return pNode->value;
}

void insert(PHashTable pHashTable, const char *key, const char *value)
{
	if (key == NULL)
		return;
	PNode pNode = findImpl(pHashTable, key);
	if (pNode)
	{
		UpdateValue(pNode, value);
		return;
	}

	pNode = NewNode(key, value);
	++pHashTable->size;
	unsigned idx = hash(key, pHashTable->capacity);
	if (pHashTable->table[idx])
	{
		pNode->next = pHashTable->table[idx];
		pHashTable->table[idx] = pNode;
	}
	else
	{
		pHashTable->table[idx] = pNode;
	}
}

void erase(PHashTable pHashTable, const char *key)
{
	if (key == NULL)
		return;

	unsigned idx = hash(key, pHashTable->capacity);
	PNode pNode = pHashTable->table[idx];
	if (pNode == NULL)
		return;

	PNode prev = NULL;
	bool found = false;

	do
	{
		if (strcmp(pNode->key, key) == 0)
		{
			found = true;
			break;
		}
		else
		{
			prev = pNode;
		}
		pNode = pNode->next;
	} while (pNode);

	if (!found)
		return;

	if (prev)
	{
		prev->next = pNode->next;
	}
	else
	{
		pHashTable->table[idx] = pNode->next;
	}
}

int main()
{
	PHashTable pHashTable = NewHashTable(HASH_TABLE_SIZE);
	insert(pHashTable, "name", "jack");
	insert(pHashTable, "age", "18");
	printf("name:%s\n", get(pHashTable, "name"));
	printf("age:%s\n", get(pHashTable, "age"));
	erase(pHashTable, "name");
	printf("name:%s\n", get(pHashTable, "name"));
	insert(pHashTable, "age", "20");
	printf("age:%s\n", get(pHashTable, "age"));
	return 0;
}
