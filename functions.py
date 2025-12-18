#this is the file that has the functions for the data cleaning and visualization part of the project
import pandas
import matplotlib.pyplot as plt
import numpy as np
###############
#todo:
# add to functions, so that it doesn't matter what type file it is/support for different filetypes (not just csv) 
################
def drop_emptycells(datasetname: str):  #works as intended
    data=pandas.read_csv(datasetname)
    data.dropna(inplace = True) #drops fully the line where one of the rows contains null or is empty
    print("dropping empty cells")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def drop_duplicates(datasetname: str): #doesn't work in conjunction with the drop emptycells
    data=pandas.read_csv(datasetname)
    data.drop_duplicates(inplace = True) #this function drops duplicates    
    print("dropping duplicates")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def data_type_check(datasetname: str): #this function checks the datatype of the first five rows of all columns, and after that converts all the values in the column to one type.  
    data=pandas.read_csv(datasetname)
    column_amount=len(data.columns) #get amount of columns
    row_amount=len(data.index)  #get amount of rows
    column_names=list(data.columns) 
    column_count=int(0) 
    data_types_array=np.empty([column_amount,5], dtype=object)
    
    if row_amount <= 5: #if the row amount is less than or equal to 5, then just check  
        print()
    else: #check the datatype of the first five rows    
        while column_count<column_amount:
            for x in range(0, 5): 
                datatype=data.iloc[x,column_count]
                print(datatype)
                if datatype.dtype=="float":
                    print('true')
                else:
                    print('false')    
                data_types_array[column_count, x]=datatype.dtype
            column_count +=1
    column_number=int(0)        
    while column_number<column_amount:
        for x in range(0, 5):
            print(data_types_array[column_number, x])
            if data_types_array[column_number, x]=="float":
                print("is float")
                data[column_names[column_number]]=data[column_names[column_number]].astype(float)
                x=4    
        column_number+=1
    print(data)            
    #check datatypes of array and if it includes float, then convert the whole column to float
    