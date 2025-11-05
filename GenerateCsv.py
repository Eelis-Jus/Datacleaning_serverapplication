import pandas as pd
import os
def generatecsv():
    BuyingPrice=[15,5.27,77.5,11,42.3,3.06,23.22,23.22]
    AmountBought=[55,100,54,1500,2,67,16,16]
    SellingPrice=[16,5.30,"null",23,55,7.5,66,66]
    Profit=[100,"null",1222,5,240,"-58",55,55]
    datadict={'BuyingPrice':BuyingPrice,'AmountBought':AmountBought,'SellingPrice':SellingPrice,'Profit':Profit}
    df = pd.DataFrame(datadict)
    if os.path.exists('test.csv'):
        os.remove('test.csv')
        df.to_csv('test.csv', index=False)
    else:    
        df.to_csv('test.csv', index=False)
