#ifndef _OBJECT_H
#define _OBJECT_H

#include <stdlib.h>

/**
 * @brief A destructor is a function used to free objects.
 *
 * @param item the item to free.
 */
typedef void (*Destructor) (void *item);

/**
 * @brief Alloc a new memory area managed by a reference counter.
 *
 * @param size The size of the memory area in bytes.
 * @param destroy A Destructor function called when reference counter reaches zero.
 * @return A pointer to the newly allocated memory area.
 */
void *
alloc (size_t size, Destructor destroy);

/**
 * @brief Return the reference counter of the given object.
 *
 * @param object A pointer to the object.
 * @return The number of references to the object.
 */
unsigned int
refsof (void *object);

/**
 * @brief Decrement the reference counter of the given object.
 *
 * @param object A pointer to the object.
 */
void
release (void *object);

/**
 * @brief Increment the reference counter of the given object.
 *
 * @param object A pointer to the object.
 */
void
retain (void *object);

#endif
