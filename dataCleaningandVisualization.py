import pandas as pd
import GenerateCsv as GC
import os
import matplotlib.pyplot as plt
print("Welcome to data cleaning and visualization program")
GC.generatecsv()
datasetName=input("Please give the name of your file")
data=pd.read_csv(datasetName)
print(data.to_string())

print("deleting the file")
if os.path.exists("test.csv"):
  os.remove("test.csv")
else:
  print("The file does not exist")

