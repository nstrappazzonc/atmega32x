#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk

windowMain = Tk()
windowMain.title('My Title')
windowMain.geometry("500x500")

notebook = ttk.Notebook(windowMain)

notebook.pack(pady=10, expand=True)

frame1 = Frame(notebook, width=400, height=280)
frame2 = Frame(notebook, width=400, height=280)

frame1.pack(fill='both', expand=True)
frame2.pack(fill='both', expand=True)

notebook.add(frame1, text='Tab 1')
notebook.add(frame2, text='Tab 2')

windowMain.mainloop()
