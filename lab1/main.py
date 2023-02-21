import sys, re  # sys - для передачи argv в QApplication
from PyQt5 import QtWidgets, QtGui
from PyQt5.QtCore import Qt

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolBar
from matplotlib.patches import Circle
import matplotlib.pyplot as plt

import design #дизайн

INP_DIGIT_ERROR = -1
INCORRECT_POINT = -2
POINTS_ERROR = -3

INDENT = 10
PIXEL = 96.358115
POINT_RADIOUS = 5
INITIAL_WIDTH = 653
INITIAL_HEIGHT = 560
MARKERSIZE = 5
EPS = 1e-8
RIGHT_BUTTON = 3


class MyApp(QtWidgets.QMainWindow, design.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        
        self.width = INITIAL_WIDTH
        self.height = INITIAL_HEIGHT
        
        self.points_x1 = []
        self.points_y1 = []
        
        self.points_x2 = []
        self.points_y2 = []

        self.figure = plt.figure(figsize=(self.width / PIXEL, self.height / PIXEL))
        self.canvas = FigureCanvas(self.figure)
        self.canvas.mpl_connect('button_press_event', self.draw_point_onclick)
        self.toolbar = NavigationToolBar(self.canvas, self)
        self.axes = self.figure.add_subplot(111)
        #self.axes.plot([1, 2, 3, 4], [5, 6, 7, 8], '*')
        
        #self.axes.plot(4, 56, '*')
        
        #c1 = Circle((4, 5), 6, fill=False)
        #self.axes.add_patch(c1)
        
        #self.axes.axis('equal')

        
        self.formLayout_3.addWidget(self.toolbar)
        self.formLayout_3.addWidget(self.canvas)
        
        self.number_of_points = 0
        self.number_first_points = 0
        self.number_second_points = 0
        
        self.lineEdit.returnPressed.connect(self.create_table) # Ввод по нажатию Enter
        self.pushButton_5.clicked.connect(self.draw_points) # Привязка отрисовки точек к кнопке
        
        
    def error_handling(self, code): # Обработчик ошибок
        match code:
            case -1:
                self.textEdit.setText("Некорректное количество точек!")
            case -2:
                self.textEdit.setText("Некорректное заполнение таблицы!")
            case -3:
                self.textEdit.setText("Точки отсутствуют!")
                
    
    def is_correct_number(self, number, string): # Проверка числовых полей на корректность
        return re.fullmatch(string, number)
      
      
    def input_number_of_points(self): # Ввод кол-ва точек
        text = self.lineEdit.text().strip()
        if self.is_correct_number(text, r'\d+ \d+') == None:
            self.number_of_points = 0
            self.error_handling(INP_DIGIT_ERROR)
        else:
            self.number_first_points, self.number_second_points = map(int, text.split())
            self.number_of_points = self.number_first_points + self.number_second_points
        self.lineEdit.clear() # стереть
        
    
    def create_table(self): # Создание таблицы
        self.input_number_of_points() # Получение количества точек
        
        if self.number_of_points == 0:
            self.tableWidget.setColumnCount(0)
            self.tableWidget.setRowCount(0)
            return
        
        self.tableWidget.setColumnCount(2) # Отображение таблицы
        self.tableWidget.setColumnWidth(0, 75)
        self.tableWidget.setColumnWidth(1, 75)
        self.tableWidget.setRowCount(self.number_of_points)
        
        
    def clear_points(self):
            self.tableWidget.clear()
            self.points_x1 = []
            self.points_y1 = []     
            self.error_handling(-2)        
        
        
    def read_points_from_one_set(self, begin, end, points_x, points_y):
        x = QtWidgets.QTableWidgetItem()
        y = QtWidgets.QTableWidgetItem()
        
        for i in range(begin, end):
            x = self.tableWidget.item(i, 0)
            y = self.tableWidget.item(i, 1)
            if x == None or y == None:
                self.clear_points()
                break
            if self.is_correct_number(x.text(), r'\d+\.?\d*') == None or self.is_correct_number(y.text(), r'\d+\.?\d*') == None:
                self.clear_points()
                break
            else:
                points_x.append(eval(x.text()))
                points_y.append(eval(y.text()))
                
        del x, y
        
        
    def get_points(self):
        self.read_points_from_one_set(0, self.number_first_points, self.points_x1, self.points_y1)
        self.read_points_from_one_set(self.number_first_points, self.number_of_points, self.points_x2, self.points_y2)
        
    
    def update_canvas(self):
        self.canvas.draw()
        self.axes.axis('equal')
        
        
    def draw_points(self):
        self.get_points()
        if self.number_first_points == 0 or self.number_second_points == 0:
            self.error_handling(POINTS_ERROR)
            return
        
        self.axes.plot(self.points_x1, self.points_y1, 'go', markersize=MARKERSIZE)
        self.axes.plot(self.points_x2, self.points_y2, 'ro', markersize=MARKERSIZE)
        self.update_canvas()
        
        
    def draw_point(self, x, y, color):
        self.axes.plot(x, y, color, markersize=MARKERSIZE)
        self.update_canvas()
        
        
    def draw_point_onclick(self, event):
        if event.button == RIGHT_BUTTON:
            sets = ('Первое множество', 'Второе множество')
            color, ok = QtWidgets.QInputDialog.getItem(self, 'В какое множество добавить точку?', 'Множества:', sets, 0, False)
            if color == 'Первое множество':
                self.draw_point(event.xdata, event.ydata, 'go')
            elif color == 'Второе множество':
                self.draw_point(event.xdata, event.ydata, 'ro')
            
        
def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()  # объект класса MyApp
    window.show()  # окно
    app.exec()
    
    
if __name__ == '__main__':
    main()
