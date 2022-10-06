from pathlib import Path
import os
result = list(Path(".").rglob("*.[hH][pP][pP]"))
result2 = list(Path(".").rglob("*.[hH]"))
rslt = result + result2

for ele in rslt:
    stra = str(ele.resolve())
    strb = str(ele.resolve().suffix)
    os.rename(stra , stra.replace(strb , ".cpp"))
