
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


