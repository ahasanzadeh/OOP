#include "SortedListClass.h"
#include "LinkedNodeClass.h"
#include <iostream>

using namespace std;

/* Default Constructor. Will properly initialize a list to be an empty list, to
 * which values can be added. */
SortedListClass::SortedListClass() {
  head = 0;
  tail = 0;
}

/* Destructor. Responsible for making sure any dynamic memory associated with an
 * object is freed up when the object is being destroyed. */
SortedListClass::~SortedListClass() { clear(); }

/* Clears the list to an empty state without resulting in any memory leaks. */
void SortedListClass::clear() {
  LinkedNodeClass *toDeletePtr = head;
  LinkedNodeClass *currentPtr = head;
  /* delete dynamic allocation nodes one by one */
  while (currentPtr != 0) {
    currentPtr = currentPtr->getNext();
    delete toDeletePtr;
    toDeletePtr = currentPtr;
  }
  head = 0;
  tail = 0;
}

/* Prints the contents of the list from head to tail to the screen.
 Begins with a line reading "Forward List Contents Follow:", then
 prints one list element per line, indented two spaces, then prints
 the line "End Of List Contents" to indicate the end of the list. */
void SortedListClass::printForward() const {
  cout << "Forward List Contents Follow:" << endl;
  LinkedNodeClass *printForwardPtr = head;
  while (printForwardPtr != 0) {
    cout << "  " << printForwardPtr->getValue() << endl;
    printForwardPtr = printForwardPtr->getNext();
  }
  cout << "End Of List Contents" << endl;
}

/* Prints the contents of the list from tail to head to the screen.
 Begins with a line reading "Backward List Contents Follow:", then
 prints one list element per line, indented two spaces, then prints
 the line "End Of List Contents" to indicate the end of the list. */
void SortedListClass::printBackward() const {
  cout << "Backward List Contents Follow:" << endl;
  LinkedNodeClass *printBackwardPtr = tail;
  while (printBackwardPtr != 0) {
    cout << "  " << printBackwardPtr->getValue() << endl;
    printBackwardPtr = printBackwardPtr->getPrev();
  }
  cout << "End Of List Contents" << endl;
}

/* Returns the number of nodes contained in the list. */
int SortedListClass::getNumElems() const {
  int countNumber;
  countNumber = 0;
  LinkedNodeClass *countPtr = head;
  while (countPtr != 0) {
    countNumber = countNumber + 1;
    countPtr = countPtr->getNext();
  }
  return countNumber;
}

/* Removes the front item from the list and returns the value that
 was contained in it via the reference parameter. If the list
 was empty, the function returns false to indicate failure, and
 the contents of the reference parameter upon return is undefined.
 If the list was not empty and the first item was successfully
 removed, true is returned, and the reference parameter will
 be set to the item that was removed. */
bool SortedListClass::removeFront(int &theVal) {
  if (getNumElems() == 0) {
    /* list is empty */
    return false;
  } else {
    /* list is not empty then remove the head */
    theVal = head->getValue();
    /* delete the pointer and first dynamic allocation node */
    head = head->getNext();
    delete head->getPrev();
    head->setPreviousPointerToNull();
    return true;
  }
}

/* Removes the last item from the list and returns the value that
 was contained in it via the reference parameter. If the list
 was empty, the function returns false to indicate failure, and
 the contents of the reference parameter upon return is undefined.
 If the list was not empty and the last item was successfully
 removed, true is returned, and the reference parameter will
 be set to the item that was removed. */
bool SortedListClass::removeLast(int &theVal) {
  if (getNumElems() == 0) {
    /* list is empty */
    return false;
  } else {
    /* list is not empty then remove the tail */
    theVal = tail->getValue();
    /* delete the pointer and last dynamic allocation node */
    tail = tail->getPrev();
    delete tail->getNext();
    tail->setNextPointerToNull();
    return true;
  }
}

/* Provides the value stored in the node at index provided in the
 0-based "index" parameter. If the index is out of range, then outVal
 remains unchanged and false is returned. Otherwise, the function
 returns true, and the reference parameter outVal will contain
 a copy of the value at that location. */
bool SortedListClass::getElemAtIndex(const int index, int &outVal) const {
  /* index out of range */
  if (index >= getNumElems()) {
    /* outVal remain unchanged */
    return false;
  } else if (index < 0) {
    /* index must start no less than zero */
    return false;
  } else {
    /* not out of range */
    int recordNum;
    recordNum = 0;
    LinkedNodeClass *recordPtr = head;
    while (recordPtr != 0) {
      if (recordNum == index) {
        outVal = recordPtr->getValue();
        return true;
      }
      recordPtr = recordPtr->getNext();
      recordNum = recordNum + 1;
    }
  }
}

/* Copy constructor. Will make a complete (deep) copy of the list, such that one
 * can be changed without affecting the other. */
SortedListClass::SortedListClass(const SortedListClass &rhs) {
  head = 0;
  LinkedNodeClass *tempNode = rhs.head;
  while (tempNode != 0) {
    this->insertValue(tempNode->getValue());
    tempNode = tempNode->getNext();
  }
  /*
  SortedListClass* copy;
  copy = new SortedListClass();
  LinkedNodeClass* currentNode = rhs.head;
  while (currentNode != 0) {
          copy->insertValue(currentNode->getValue());
          currentNode = currentNode->getNext();
  }
  // head = copy->head;
  head = copy->head;
  tail = copy;
  */
}

/* Allows the user to insert a value into the list. Since this
 is a sorted list, there is no need to specify where in the list
 to insert the element. It will insert it in the appropriate
 location based on the value being inserted. If the node value
 being inserted is found to be "equal to" one or more node values
 already in the list, the newly inserted node will be placed AFTER
 the previously inserted nodes. */
void SortedListClass::insertValue(const int &valToInsert) {
  // paratmeter is the value to insert into the list

  // list is empty then the only node up to now
  if (head == 0) {
    LinkedNodeClass *insertPtr;
    insertPtr = new LinkedNodeClass(0, valToInsert, 0);
    // head and tail point to this node
    head = insertPtr;
    tail = insertPtr;
  } else {
    // list is not empty thus compare
    LinkedNodeClass *temp = head;

    while ((temp != 0) && (temp->getValue() <= valToInsert)) {
      temp = temp->getNext();
    }

    // need to insert value before this temp point node
    if (temp == head) {
      // insert first position
      LinkedNodeClass *insertPtr;
      insertPtr = new LinkedNodeClass(0, valToInsert, head);
      insertPtr->setBeforeAndAfterPointers();
      // update head and tail
      head = insertPtr;
    } else if (temp == 0) {
      // insert the last postion
      LinkedNodeClass *insertPtr;
      insertPtr = new LinkedNodeClass(tail, valToInsert, 0);
      insertPtr->setBeforeAndAfterPointers();
      tail = insertPtr;
    } else {
      // insert in the middle position
      // should insert before temp and after its previous node
      // no need to change tail and head here
      LinkedNodeClass *insertPtr;
      insertPtr = new LinkedNodeClass(temp->getPrev(), valToInsert, temp);
      insertPtr->setBeforeAndAfterPointers();
    }
  }
}