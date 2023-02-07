from pathlib import Path
import os
result = list(Path(".").rglob("*.[hH][pP][pP]"))
result2 = list(Path(".").rglob("*.[hH]"))
result3 = list(Path(".").rglob("*.cpp"))



rslt = result + result2 + result3

for ele in rslt:
    print(ele)
    filedata = ''
    with open(ele,'r') as file:
        filedata = file.read()
    
    filedata = filedata.replace('é','eh').replace('ã','a').replace('á','a').replace('ç','c').replace('ê','e')
    filedata = filedata.replace('ó','o').replace('ú','u').replace('Ã','A')
    filedata = filedata.replace('Ç','C').replace('õ','o')
    

    with open(ele,'w') as file:
        file.write(filedata)