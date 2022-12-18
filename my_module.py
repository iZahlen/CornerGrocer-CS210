import re
import string
from collections import Counter                           

def read_File():

    # This function will read a file
    # It will count the total amount of each product
    # Then it will print it to the console
   
    token = open("Products.txt") 
    products = token.read().split() #creates object that holds each line info from token object
    
    unique_Product = sorted(set(products))

    for word in unique_Product:
        print("_____________________________________")
        print("")
        print(word, ": ",  products.count(word))
        print("_____________________________________")
    

    token.close()

    

def locate_Total_Product_Amount(v):

    # Takes a string from C++ user input
    # searches through text file to count the total occurance of item
    # then prints the frequency

    token = open("Products.txt")
    products = token.read().split() #creates object that holds each line info from token object
    unique_Product = sorted(set(products)) 
    token.close() 


    tot = 0 
    tot_inventory = 0 
    tot_inventory_count = 0 

    for word in unique_Product: # get total amount of items in list -- works better then len(list) due to how set is sorted
        tot_inventory_count += 1

    for word in unique_Product: #finds the element in unique_Product that is the requested string from user
        temp_String = word
        tot_inventory += 1
        if (temp_String == v):
            tot = products.count(word)
            tot_inventory -= 1 
        if (temp_String != v and tot_inventory == tot_inventory_count):
            return -1 

    
    
    return tot


def read_AND_Write_File():

    # Takes information from text file
    # counts product and sorts items and their frequency 
    # takes the sorted and counted items and writes to a dat file
    # will then print histogram

    token = open("Products.txt")
    data = open("frequency.dat", "w")
    products = token.read().split() #creates object that holds each line info from token object
    unique_Product = sorted(set(products)) #sorts the items


    #Writes the data to the .dat file
    for word in unique_Product:
        data.write(word)
        data.write(" ")
        data.write(str(products.count(word)))
        data.write("\n")
    
    data.close() # Closes file so it can be re-opened as read-only below

    histo_data = open("frequency.dat", "r") 
    product_data = histo_data.readlines() # read lines so each product is matched it's corresponding frequency


    # Variables used for nested for loops
    temp_freq = 0
    temp_product = ""

    # Reads and prepares data from .dat file for histogram
    for line in product_data:
        temp_int = 0
        temp_string = line.split() #splits product name and frequency
        for word in temp_string:
            temp_int += 1
            if (temp_int == 1):
                temp_product = word #product
                print("____________________________________")
                print("")
                print(temp_product, end = " ")
            if (temp_int == 2):
                temp_freq = int(word) #frequency
        

        # Creates the histogram -- example output: Apples ****
        for i in range(temp_freq):
            print("+", end = "")
        print("")
        print("____________________________________")
        print("")
        
    