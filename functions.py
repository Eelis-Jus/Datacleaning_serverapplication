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
    print("dropping empty cells")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def drop_duplicates(datasetname: str): #doesn't work in conjunction with the drop emptycells
    data=pandas.read_csv(datasetname)
    data.drop_duplicates(inplace = True) #this function drops duplicates    
    print("dropping duplicates")
    print(data.to_string())
    data.to_csv(datasetname, index=False)

def data_type_check_and_validation(datasetname: str): 
    data=pandas.read_csv(datasetname)
    column_amount=len(data.columns) #get amount of columns
    row_amount=len(data.index)  #get amount of rows
    if row_amount <= 5: #if the row amount is less than or equal to 5, then just check  
        print()
    else: #check the datatype of the first five rows
        column_count=int(0) 
        d_types_arr=[['']*column_amount]*5
        while column_count<6:
            for x in range(1, 6):
                datatype=data.iloc[x,column_count]
                print(datatype)
            column_count +=1    
    #data.to_csv(datasetname, index=False)