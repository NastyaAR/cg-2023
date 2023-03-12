import numpy as np
import matplotlib.pyplot as plt

x = ['Стандарт', 'ЦДА', 'Брезенхем', 'Брезенхем\nцелочисленный', 'Брезенхем с устранением\nступенчатости', 'Ву']

file = open('/home/nastya/sem4/cg-2023/lab_03/time.txt', 'r')
y = file.readline().split()
z = [1, 2, 3, 4, 5, 6]

fig, ax = plt.subplots()

ax.plot(x, y, "-*")

ax.set_facecolor('seashell')
fig.set_facecolor('floralwhite')
fig.set_figwidth(12)    #  ширина Figure
fig.set_figheight(6)    #  высота Figure

plt.title("Сравнение эффективности")

plt.show()

file.close()