#this is the file that has the functions for the data cleaning and visualization part of the project
import pandas
import chardet
import matplotlib.pyplot as plt
import numpy as np
from pandas.api.types import is_string_dtype

###############
#todo:
# add to functions, so that it doesn't matter what type file it is/support for different filetypes (not just csv) 
################

def drop_emptycells(datasetname: str):  #works as intended
    with open(datasetname, 'rb') as f: #check and use the proper encoding for the file
        raw_data= f.read()
        result=chardet.detect(raw_data)
        encoding=result['encoding']
    data=pandas.read_csv(datasetname, encoding=encoding)
    data.dropna(inplace = True) #drops fully the line where one of the rows contains null or is empty
    print("dropping empty cells")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def drop_duplicates(datasetname: str): #doesn't work in conjunction with the drop emptycells
    with open(datasetname, 'rb') as f: #check and use the proper encoding for the file
        raw_data= f.read()
        result=chardet.detect(raw_data)
        encoding=result['encoding']
    data=pandas.read_csv(datasetname, encoding=encoding)
    data.drop_duplicates(inplace = True) #this function drops duplicates    
    print("dropping duplicates")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def data_type_check(datasetname: str): #this function checks the datatype of the first five rows of all columns, and after that converts all the values in the column to one type.  
    with open(datasetname, 'rb') as f: #check and use the proper encoding for the file
        raw_data= f.read()
        result=chardet.detect(raw_data)
        encoding=result['encoding']
    data=pandas.read_csv(datasetname, encoding=encoding)
    data #?
    column_amount=len(data.columns) #get amount of columns
    row_amount=len(data.index)  #get amount of rows
    column_names=list(data.columns) 
    column_count=int(0) 
    data_types_array=np.empty([column_amount,5], dtype=object) #array to store first 5 datatypes of each column
    
    while column_count<column_amount: #while loop to store first 5 datatypes of each column
            for x in range(0, 5): 
                datatype=data.iloc[x,column_count] #datatype name for the variable is slightly misleading, because it holds the value of the particular row of the column 
                print(datatype)
                isString=isinstance(datatype, str)                
                if isString==True:
                    data_types_array[column_count, x]=pandas.StringDtype()
                    print(data_types_array[column_count, x])
                else:    
                    data_types_array[column_count, x]=datatype.dtype
            column_count +=1
    column_number=int(0)        
    while column_number<column_amount:
        for x in range(0, 5):
            print(data_types_array[column_number, x])
            if data_types_array[column_number, x]=="float": #if one of the values of the column is a float, then convert the column values to float
                print("is float")
                data[column_names[column_number]]=data[column_names[column_number]].astype(float)
                x=4    
        column_number+=1
    data.to_csv(datasetname, index=False)

def report_of_the_file(datasetname: str): #this is the function that will make some sort of automatic report of the csv file
    with open(datasetname, 'rb') as f: #check and use the proper encoding for the file
        raw_data= f.read()
        result=chardet.detect(raw_data)
        encoding=result['encoding']

