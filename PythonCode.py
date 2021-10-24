# John Hanks
# CS 210: 7-1 Project Three
# 10/17/2021

import re
import string

grocerDict = {} # Creates an empty dictionary
produceList = [] # Creates an empty list

def PrintMenu(): # Menu function to display user's menu options
    print("   ******************************")
    print("   |         Weclcome to        |")
    print("   |        Corner Grocer       |")
    print("   ******************************")
    print("   |        Menu Options        |")
    print("   | 1: Display a Grocery List  |")
    print("   | 2: Item Frequency          |")
    print("   | 3: Histogram               |")
    print("   | 4: Exit                    |")
    print("   |                            |")
    print("   | Enter your selection as    |") 
    print("   | a number 1, 2, 3 or 4.     |")
    print("   ******************************\n")
    # Asks for selection, storage with C++ code

def ListCreation(): # Function to read the ShoppingList.txt and created a dictionary with the item and frequency.
    with open('ShoppingList.txt') as grocerList:
       tempList = grocerList.readlines() # Reads each line in the file and adds to temp list
       tempList.sort() # Sorts the list A-Z

       # FOR loop to remove the newline from each item in list
       for produceItem in tempList:
           produceList.append(produceItem.strip('\n'))

       # FOR loop to apppend grocerDict by adding the item as the key and the frequency count
       for produceItem in produceList:
           if produceItem in grocerDict.keys():
                value = grocerDict[produceItem]
                grocerDict[produceItem] = value + 1
           else:
                grocerDict[produceItem] = 1

 # This Function create the table for the produce items and their frequency. Menu option 1
def GroceryListFreq():
    print("   Produce Items Purchased Today")
    print('-' * 36)
    ListCreation()
    format_string = '{item:^18}{number:>14}'
    print(format_string.format(item = 'Produce Item', number = 'Amount Purchased'))
    print('_' * 36)
    print()
    format_string = '{item:>14}{number:.>14}'
    for produceItem, count in grocerDict.items(): # FOR loop for the printing of each item and frequency
        print(format_string.format(item = produceItem, number = count))
 
 # This function returns the fequency value of user's specific item. Menu option 2
def GroceryItemFreq(item):
    ListCreation()
    groceryItem = item.capitalize() # Capitalizes the first character of the word. Check as apples to user is the same as Apples.
    if groceryItem in grocerDict.keys():
        num = grocerDict.get(groceryItem)
        return num
    else:
        return -1 # Returns -1 if the item does not show up in the dictionary.

# This function creates the "dat" file to be read by the C++ to create the histogram. Menu option 3
def GrocerHistogram():
    ListCreation()
    with open('frequency.dat', 'w') as histogram:
        for key in grocerDict.keys():
            histogram.write('{} {}'.format(key, grocerDict.get(key)))