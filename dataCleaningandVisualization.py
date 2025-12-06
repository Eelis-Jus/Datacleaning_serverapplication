import pandas as pd
import GenerateCsv as GC
import functions as ft
import os
import sys
import matplotlib.pyplot as plt
print("Welcome to data cleaning and visualization program")
filename=sys.argv[1]
#GC.generatecsv()
#datasetName=input("Please give the name of your file: ")
print('data preprocessing') #delete this eventually
data=pd.read_csv(filename)
print(data.to_string())
ft.drop_duplicates(filename) 
ft.drop_emptycells(filename)
#data.to_csv(filename, index=False)
print('data processed')

#print("deleting the file")
#if os.path.exists("test.csv"):
#  os.remove("test.csv")
#else:
#  print("The file does not exist")

