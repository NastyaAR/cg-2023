import matplotlib.pyplot as plt

file = open('/home/nastya/sem4/cg-2023/lab_03/time.txt', 'r')
times = file.readline().split()

for i in range(len(times)):
    times[i] = float(times[i].replace(",", "."))
    
print(times)
    
file.close()

plt.figure(1, figsize=(12, 7))

plt.title("Сравнение эффективности")

y = range(len(times))

labels = ('Стандарт', 'ЦДА', 'Брезенхем', 'Брезенхем\nцелочисленный', 'Брезенхем с устранением\nступенчатости', 'Ву')

plt.bar(y, times)
plt.xticks(y, labels)

plt.ylabel("Время в мкс.\n")
plt.show()
