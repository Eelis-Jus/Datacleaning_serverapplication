import pandas as pd
#import GenerateCsv as GC
import functions as ft
import os
import chardet
import sys
import matplotlib.pyplot as plt
print("Welcome to data cleaning and visualization program")
filename=sys.argv[1] #this is for the actual usage
#filename='test.csv' #this is for testing 
#GC.generatecsv() #this is for testing
#datasetName=input("Please give the name of your file: ") #this also for testing
with open(filename, 'rb') as f: #check and use the proper encoding for the file
    raw_data= f.read()
    result=chardet.detect(raw_data)
    encoding=result['encoding']
data=pd.read_csv(filename, encoding=encoding)
    
print(data.to_string())
ft.drop_duplicates(filename) #this is for testing and usage
ft.drop_emptycells(filename) #this is for testing and usage-  
ft.data_type_check(filename)
print(filename)
#data.to_csv(filename, index=False)
print('data processed')

#print("deleting the file")
#if os.path.exists("test.csv"):
#  os.remove("test.csv")
#else:
#  print("The file does not exist")

