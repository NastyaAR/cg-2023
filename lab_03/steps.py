import matplotlib.pyplot as plt

file = open('/home/nastya/sem4/cg-2023/lab_03/gradation.txt', 'r')
algorithms = []
for i in range(5):
    times = file.readline().split()
    for i in range(len(times)):
        times[i] = int(times[i].replace(",", "."))
    algorithms.append(times)
    
file.close()

labels = ('ЦДА', 'Брезенхем', 'Брезенхем\nцелочисленный', 'Брезенхем с устранением\nступенчатости', 'Ву')

for i in range(5):
    plt.figure(i, figsize=(12, 7))
    plt.title(labels[i])

    y = range(0, 91)
    plt.bar(y, algorithms[i])
    #plt.xticks(y, labels)
    plt.ylabel("Количество ступенек\n")
    plt.xlabel("Угол\n")

plt.show()
