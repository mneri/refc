#include <assert.h>
#include <stdlib.h>

#include "refc.h"

#define OBJECT_TO_RECORD(object) ((ObjectRecord *) (((char *) object) - sizeof (ObjectRecord)))
#define RECORD_TO_OBJECT(record) ((void *) (((char *) record) + sizeof (ObjectRecord)))

typedef struct {
  unsigned int count;
  Destructor destroy;
} ObjectRecord;

void *
alloc (size_t size, Destructor destroy)
{
  ObjectRecord *record = (ObjectRecord *) malloc (sizeof (ObjectRecord) + size);

  if (record != NULL)
    {
      record->count = 0;
      record->destroy = destroy;
      return RECORD_TO_OBJECT (record);
    }

  return NULL;
}

unsigned int
refsof (void *object)
{
  ObjectRecord *record = OBJECT_TO_RECORD (object);
  return record->count;
}

void
release (void *object)
{
  int count;
  ObjectRecord *record;

  record = OBJECT_TO_RECORD (object);
  count = __sync_sub_and_fetch (&(record->count), 1);
  assert (!(count < 0));

  if (count == 0)
    {
      if (record->destroy != NULL)
	{
	  record->destroy (object);
	}

      free (record);
    }
}

void
retain (void *object)
{
  ObjectRecord *record = OBJECT_TO_RECORD (object);
  __sync_add_and_fetch (&(record->count), 1);
}
