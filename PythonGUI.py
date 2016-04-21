
from Tkinter import *
import os

root = Tk(className ="Parallel tester GUI")

Label(root, text=" Parameters ").grid(row = 1, column = 0)
Label(root, text=" Number of nodes : ").grid(row = 1, column = 1)
Label(root, text=" Total Search : ").grid(row = 1, column = 3)
Label(root, text=" Packet size : ").grid(row = 1, column = 5)
Label(root, text=" Percision (area only): ").grid(row = 1, column = 7)

numberOfNodes = StringVar() # defines the widget state as string
Entry(root, textvariable = numberOfNodes).grid(row = 1, column = 2)

totalSearch = StringVar() # defines the widget state as string
Entry(root, textvariable = totalSearch).grid(row = 1, column = 4)

packetSize = StringVar() # defines the widget state as string
Entry(root, textvariable = packetSize).grid(row = 1, column = 6)

percision = StringVar() # defines the widget state as string
Entry(root, textvariable = percision).grid(row = 1, column = 8)


def runPrimes():
    os.system("mpirun -np " + numberOfNodes.get() + " primesfour " + totalSearch.get() + " " + packetSize.get())
Button(root, text=" Find prime numbers ", command=runPrimes).grid(row = 2, column = 0)

def runPrimes():
    os.system("mpirun -np " + numberOfNodes.get() + " areaunder " + totalSearch.get() + " " + packetSize.get() + " " + percision.get())
Button(root, text=" Find the area under a curve ", command=runPrimes).grid(row = 2, column = 1)

fii = Button(root, text="Quit", command = root.quit).grid(row = 2, column = 2)

root.mainloop()



'''






from Tkinter import *
import os

root = Tk(className ="My first GUI")

Label(root, text=" FindPrimes ").grid(row = 0, column = 0)
Label(root, text=" Number of nodes : ").grid(row = 0, column = 1)
Label(root, text=" Total Search : ").grid(row = 0, column = 3)
Label(root, text=" Packet size : ").grid(row = 0, column = 5)

PNN = StringVar() # defines the widget state as string
Entry(root,textvariable=PNN).grid(row = 0, column = 2)

PTotS = StringVar() # defines the widget state as string
Entry(root,textvariable=PTotS).grid(row = 0, column = 4)

PPsize = StringVar() # defines the widget state as string
Entry(root,textvariable=PPsize).grid(row = 0, column = 6)

Label(root, text=" AreaUnderCurve ").grid(row = 1, column = 0)
Label(root, text=" Number of nodes : ").grid(row = 1, column = 1)
Label(root, text=" Total Search : ").grid(row = 1, column = 3)
Label(root, text=" Packet size : ").grid(row = 1, column = 5)
Label(root, text=" Percision : ").grid(row = 1, column = 7)

ANN = StringVar() # defines the widget state as string
Entry(root,textvariable=ANN).grid(row = 1, column = 2)

ATotS = StringVar() # defines the widget state as string
Entry(root,textvariable=ATotS).grid(row = 1, column = 4)

APsize = StringVar() # defines the widget state as string
Entry(root,textvariable=APsize).grid(row = 1, column = 6)

APercision = StringVar() # defines the widget state as string
Entry(root,textvariable=APercision).grid(row = 1, column = 8)


def runPrimes():
    os.system("mpirun -np " + PNN.get() + " primesfour " + PTotS.get() + " " + PPsize.get())
Button(root,text=" Run FindPrimes ", command=runPrimes).grid(row = 2, column = 0)

def runPrimes():
    os.system("mpirun -np " + ANN.get() + " areaunder " + ATotS.get() + " " + APsize.get + " " + APercision.get())
Button(root,text=" Run FindPrimes ", command=runPrimes).grid(row = 2, column = 1)

fii = Button(root,text="Quit", command = root.quit).grid(row = 2, column = 8)

root.mainloop()




----------------------------------------------------------------------------------------------------

from Tkinter import *
import os

root = Tk(className ="My first GUI")


l = Label(root, text="Number of nodes").grid(row = 0)

svalue = StringVar() # defines the widget state as string
w = Entry(root,textvariable=svalue)

def act():
    os.system("mpirun -np " + svalue.get() + " primesfour")
foo = Button(root,text="Run", command=act)
foo.pack(side = LEFT, padx = 3, pady = 5)

def compile():
    os.system("mpicc -o primesfour PrimesParallelFour.c")
fer = Button(root,text="Compile", command=compile)
fer.pack(side = LEFT, padx = 3, pady = 5)

fii = Button(root,text="Quit", command = root.quit)
fii.pack(side = LEFT, padx = 3, pady = 5)

root.mainloop()




    Label(master, text="First").grid(row=0)
    Label(master, text="Second").grid(row=1)

    e1 = Entry(master)
    e2 = Entry(master)

    e1.grid(row=0, column=1)
    e2.grid(row=1, column=1)

    '''


