 # Module sys has to be imported:
import sys
import numpy as np
from pybdm import BDM
from pybdm import options


options.set(raise_if_zero=False)

file = sys.argv[1]
with open(file, 'r') as file:
    data = file.read().replace('\n', '')


tape = np.fromstring(data, dtype=int,sep='-')
bdm = BDM(ndim=1,nsymbols=2)
value = bdm.nbdm(tape)
value2 = bdm.nent(tape)
if value2==data:
    value2=0
if (value==0 and (np.isnan(value2)==False) and value2>0.0) or ( value2<value and value2>0.0):
    value = value2

print(value)
