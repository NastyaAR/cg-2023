import sys, re, copy  # sys - для передачи argv в QApplication
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
LEFT_BUTTON = 1
GREEN = QtGui.QColor(144, 238, 144)
RED = QtGui.QColor(240, 128, 128)
RAD_EPS = 0.05

ADD = 'add'
DEL = 'del'
DEL_ALL = 'del_all'
DRAW = 'draw'
TASK = 'task'
TABLE = 'table'


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
        
        self.from_line_edit = False
        
        self.figure, self.canvas, self.toolbar, self.axes = None, None, None, None
        self.init_plot()
        
        self.command_stack = []
        self.states = []
        
        #c1 = Circle((4, 5), 6, fill=False)
        #self.axes.add_patch(c1)
        
        self.number_of_points = 0
        self.number_first_points = 0
        self.number_second_points = 0
        self.current_state = {'number1': self.number_first_points, 'number2': self.number_second_points, 'all': self.number_of_points, 'point_x1': self.points_x1, 'point_y1': self.points_y1, 'point_x2': self.points_x2, 'point_y2': self.points_y2}
        
        self.lineEdit.returnPressed.connect(self.create_table) # Ввод по нажатию Enter
        self.pushButton_5.clicked.connect(self.draw_points) # Привязка отрисовки точек к кнопке
        self.pushButton.clicked.connect(self.delete_point_from_table) # Удаление точки из таблицы по нажатию кнопки
        self.pushButton_6.clicked.connect(self.add_point_in_table_from_button) # Добавление точки по нажатию кнопки
        self.pushButton_4.clicked.connect(self.delete_all) # Стереть всё
        self.pushButton_2.clicked.connect(self.cancel)
        
        
        
    def init_plot(self): # График
        self.figure = plt.figure(figsize=(self.width / PIXEL, self.height / PIXEL))
        self.canvas = FigureCanvas(self.figure)
        self.canvas.mpl_connect('button_press_event', self.draw_point_onclick)
        self.toolbar = NavigationToolBar(self.canvas, self)
        self.axes = self.figure.add_subplot(111)
        self.formLayout_3.addWidget(self.toolbar)
        self.formLayout_3.addWidget(self.canvas)
        
        
    def uninit_plot(self):
        self.formLayout_3.removeRow(self.toolbar)
        self.formLayout_3.removeRow(self.canvas)
        del self.figure, self.canvas, self.toolbar, self.axes
        
        
    def error_handling(self, code): # Обработчик ошибок
        match code:
            case -1:
                self.textEdit.setText("Некорректное количество точек!")
            case -2:
                self.textEdit.setText("Некорректное заполнение таблицы!")
            case -3:
                self.textEdit.setText("Точки отсутствуют!")
            case -4:
                self.textEdit.setText("Некорректный ввод координат!")
                
    
    def is_correct_number(self, number, string): # Проверка числовых полей на корректность
        return re.fullmatch(string, number)
      
      
    def input_number_of_points(self): # Ввод кол-ва точек
        text = self.lineEdit.text().strip()
        if self.is_correct_number(text, r'\d+ \d+') == None:
            self.number_of_points = 0
            self.current_state['all'] = 0
            self.error_handling(INP_DIGIT_ERROR)
        else:
            self.number_first_points, self.number_second_points = map(int, text.split())
            self.current_state['number1'], self.current_state['number2'] = map(int, text.split())
            self.number_of_points = self.number_first_points + self.number_second_points
            self.current_state['all'] = self.number_first_points + self.number_second_points
        self.lineEdit.clear() # стереть
        
    
    def create_table(self): # Создание таблицы
        if self.from_line_edit == False: 
            self.input_number_of_points() # Получение количества точек
            number = self.number_of_points
            number = self.current_state['all']
        else:
            number = 1
        if self.current_state['all'] == 0 and self.from_line_edit == False:
            self.tableWidget.setColumnCount(0)
            self.tableWidget.setRowCount(0)
            return
        
        self.tableWidget.setColumnCount(2) # Отображение таблицы
        self.tableWidget.setColumnWidth(0, 75)
        self.tableWidget.setColumnWidth(1, 75)
        self.tableWidget.setRowCount(number)
        
        self.command_stack.append(TABLE)
        
        
    def clear_points(self):
            self.tableWidget.clear()
            self.points_x1 = []
            self.current_state['point_x1'] = []
            self.points_y1 = []
            self.current_state['point_y1'] = []     
            self.error_handling(-2)        
        
        
    def read_points_from_one_set(self, begin, end, points_x, points_y):
        x = QtWidgets.QTableWidgetItem()
        y = QtWidgets.QTableWidgetItem()
        
        for i in range(begin, end):
            x = self.tableWidget.item(i, 0)
            y = self.tableWidget.item(i, 1)
            if begin == 0 and self.current_state['number1'] != 0:
                x.setBackground(GREEN)
                y.setBackground(GREEN)
            else:
                x.setBackground(RED)
                y.setBackground(RED)
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
        self.read_points_from_one_set(0, self.current_state['number1'], self.current_state['point_x1'], self.current_state['point_y1'])
        self.read_points_from_one_set(self.current_state['number1'], self.current_state['all'], self.current_state['point_x2'], self.current_state['point_y2'])
        
    
    def update_canvas(self):
        self.canvas.draw()
        self.axes.axis('equal')
        
        
    def draw_points(self, from_table):
        if from_table == False: self.get_points()
        if self.current_state['number1'] == 0 and self.current_state['number2'] == 0:
            self.error_handling(POINTS_ERROR)
            return
        
        if self.current_state['point_x1']: self.axes.plot(self.current_state['point_x1'], self.current_state['point_y1'], 'go', markersize=MARKERSIZE)
        if self.current_state['point_x2']: self.axes.plot(self.current_state['point_x2'], self.current_state['point_y2'], 'ro', markersize=MARKERSIZE)
        self.update_canvas()
        
        if from_table == False: 
            self.command_stack.append(DRAW)
            self.states.append(copy.deepcopy(self.current_state))
        
        
    def draw_point(self, x, y, color):
        self.axes.plot(x, y, color, markersize=MARKERSIZE)
        self.update_canvas()
        
        
    def insert_row(self, x, y, ind, color):
        new_x = QtWidgets.QTableWidgetItem()
        new_y = QtWidgets.QTableWidgetItem()
        
        if ind == 0: 
            self.from_line_edit = True
            self.create_table()
            self.from_line_edit = False
        else: 
            self.tableWidget.insertRow(ind)
        self.tableWidget.setItem(ind, 0, QtWidgets.QTableWidgetItem('{:.3f}'.format(x)))
        self.tableWidget.setItem(ind, 1, QtWidgets.QTableWidgetItem('{:.3f}'.format(y)))
        new_x = self.tableWidget.item(ind, 0)
        new_y = self.tableWidget.item(ind, 1)
        new_x.setBackground(color)
        new_y.setBackground(color)
        ind += 1
        
        del new_x, new_y
        
        
    def add_point_in_table(self, x, y, color):
        if color == 'green':
            self.insert_row(x, y, self.current_state['number1'], GREEN)
            self.current_state['point_x1'].append(x)
            self.current_state['point_y1'].append(y)
            self.current_state['number1'] += 1
        elif color == 'red':
            self.insert_row(x, y, self.current_state['number1'] + self.current_state['number2'], RED)
            self.current_state['point_x2'].append(x)
            self.current_state['point_y2'].append(y)
            self.current_state['number2'] += 1
        self.current_state['all'] += 1
        
        
    def delete_point(self, point_x, point_y, ind, ind_in_table):
        if point_x: point_x.pop(ind)
        if point_y: point_y.pop(ind)
        self.tableWidget.removeRow(ind_in_table)
        
        
    def redrawing_plot(self, i):
        self.uninit_plot()
        self.init_plot()
        if i >= self.current_state['number1']:
            self.delete_point(self.current_state['point_x2'], self.current_state['point_y2'], i - self.current_state['number1'], i)
            self.current_state['number2'] -= 1
            self.current_state['all'] -= 1
        elif i >= 0:
            self.delete_point(self.current_state['point_x1'], self.current_state['point_y1'], i, i)
            self.current_state['number1'] -= 1
            self.current_state['all'] -= 1
        self.draw_points(True)
        
        
    def draw_point_onclick(self, event):
        if event.button == RIGHT_BUTTON:
            self.states.append(copy.deepcopy(self.current_state))
            sets = ('Первое множество', 'Второе множество')
            color, ok = QtWidgets.QInputDialog.getItem(self, 'В какое множество добавить точку?', 'Множества:', sets, 0, False)
            if color == 'Первое множество' and ok:
                self.draw_point(event.xdata, event.ydata, 'go')
                self.add_point_in_table(event.xdata, event.ydata, 'green')
            elif color == 'Второе множество' and ok:
                self.draw_point(event.xdata, event.ydata, 'ro')
                self.add_point_in_table(event.xdata, event.ydata, 'red')
            elif not ok:
                return
            self.command_stack.append(ADD)
            print(self.states)
        if event.button == LEFT_BUTTON:
            self.states.append(copy.deepcopy(self.current_state))
            set_1 = [(self.current_state['point_x1'][i], self.current_state['point_y1'][i]) for i in range(self.current_state['number1'])]
            set_2 = [(self.current_state['point_x2'][i], self.current_state['point_y2'][i]) for i in range(self.current_state['number2'])]

            all_points = set_1 + set_2
            for i in range(self.current_state['all']):
                if event.xdata and event.ydata and all_points[i][0] - RAD_EPS <= event.xdata <= all_points[i][0] + RAD_EPS and all_points[i][1] - RAD_EPS <= event.ydata <= all_points[i][1]:
                    self.redrawing_plot(i)
                    self.command_stack.append(DEL)
                    break
            
                
        
    def delete_point_from_table(self):
        self.states.append(copy.deepcopy(self.current_state))
        if (ind := self.tableWidget.currentRow()) != -1:
            self.redrawing_plot(ind)
        self.command_stack.append(DEL)
            
            
    def add_point_in_table_from_button(self):
        sets = ('Первое множество', 'Второе множество')
        color, ok = QtWidgets.QInputDialog.getItem(self, 'В какое множество добавить точку?', 'Множества:', sets, 0, False)
        
        if ok:
            point, ok = QtWidgets.QInputDialog.getText(self, 'Введите координаты добавляемой точки', 'Координаты (через пробел):')
        else:
            return
        
        if self.is_correct_number(point, r'\d+\.?\d* \d+\.?\d*') == None:
            self.error_handling(-4)
            return
        
        self.states.append(copy.deepcopy(self.current_state))
        x, y = map(float, point.split())
        if color == 'Первое множество':
            self.draw_point(x, y, 'go')
            self.add_point_in_table(x, y, 'green')
        elif color == 'Второе множество':
            self.draw_point(x, y, 'ro')
            self.add_point_in_table(x, y, 'red')
        
        self.command_stack.append(ADD)
            
            
    def delete_all(self):
        self.states.append(copy.deepcopy(self.current_state))
        self.lineEdit.clear()
        self.clear_points()
        self.textEdit.clear()
        self.uninit_plot()
        self.init_plot()
        self.current_state['point_x1'] = []
        self.current_state['point_y1'] = []
        self.current_state['point_x2'] = []
        self.current_state['point_y2'] = []
        self.from_line_edit = False
        self.current_state['all'] = 0
        self.current_state['number1'] = 0
        self.current_state['number2'] = 0
        self.command_stack.append(DEL_ALL)
        
        
    def undo_table(self, state):
        for i in range(state['number1']):
            self.insert_row(state['point_x1'][i], state['point_y1'][i], i, GREEN)
        for i in range(state['number2']):
            self.insert_row(state['point_x2'][i], state['point_y2'][i], i + state['number1'], RED)
        
        
    def cancel(self):
        last_action = self.command_stack.pop()
        last_state = self.states.pop()
        self.current_state = copy.deepcopy(last_state)
        if last_action == DEL_ALL or last_action == ADD or last_action == DEL:
            self.undo_table(last_state)
            self.redrawing_plot(-1)
        elif last_action == DRAW:
            self.uninit_plot()
            self.init_plot()
            
        
        
def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()  # объект класса MyApp
    window.show()  # окно
    app.exec()
    
    
if __name__ == '__main__':
    main()
