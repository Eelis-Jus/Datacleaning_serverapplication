#this is the file that has the functions for the data cleaning and visualization part of the project
import pandas
import matplotlib.pyplot as plt
###############
#todo:
# add to functions, so that it doesn't matter what type file it is/support for different filetypes (not just csv) 
################
def drop_emptycells(datasetname: str):  #works as intended
    data=pandas.read_csv(datasetname)
    data.dropna(inplace = True) #drops fully the line where one of the rows contains null or is empty
    print(data.to_string())

def drop_duplicates(datasetname: str): #works as intended
    data=pandas.read_csv(datasetname)
    data.drop_duplicates(inplace = True) #this function drops duplicates    
    print(data.to_string())



#def makeE