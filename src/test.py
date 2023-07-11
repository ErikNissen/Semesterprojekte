import sys
from PyQt5.QtWidgets import *
import requests
import sqlite3

class RecipeWindow(QDialog):
    def __init__(self, name, ingredients, instructions):
        ingredients = ingredients.replace(",", "\n")
        super().__init__()
        self.setWindowTitle(name)
        self.setGeometry(500, 500, 600, 400)
        self.text_editor = QTextEdit(self)
        self.text_editor.setReadOnly(True)
        self.text_editor.setText(f"<h2>Ingredients</h2>{ingredients}<h2>Instructions</h2>{instructions}")
        self.show()


def save_to_database(name, ingredients, instructions):
    conn = sqlite3.connect('cocktails.db')
    c = conn.cursor()
    c.execute("SELECT * FROM cocktails WHERE name=?", (name,))
    result = c.fetchone()
    if result is None:
        c.execute("INSERT INTO cocktails (name, ingredients, instructions) VALUES (?,?,?)", (name, ingredients, instructions))
        conn.commit()
    conn.close()


class CocktailDatabase(QWidget):
    def __init__(self):
        super().__init__()

        # Set up the user interface
        self.search_bar = QLineEdit(self)
        self.search_bar.move(20, 20)
        self.search_bar.resize(280, 40)

        self.search_button = QPushButton('Search', self)
        self.search_button.move(320, 20)
        self.search_button.clicked.connect(self.search)

        self.result_list = QListWidget(self)
        self.result_list.move(20, 80)
        self.result_list.resize(380, 360)
        self.result_list.itemClicked.connect(self.show_recipe)

        self.show()

    def search(self):
        search_query = self.search_bar.text()
        conn = sqlite3.connect('cocktails.db')
        c = conn.cursor()
        c.execute("SELECT name FROM cocktails WHERE name LIKE ?", (search_query+'%',))
        result = c.fetchall()
        if result:
            self.result_list.clear()
            for drink in result:
                self.result_list.addItem(drink[0])
        else:
            url = f'https://www.thecocktaildb.com/api/json/v1/1/search.php?f' \
                  f'={search_query}'
            response = requests.get(url)
            data = response.json()
            self.result_list.clear()
            for drink in data['drinks']:
                name = drink['strDrink']
                ingredients = ', '.join([drink[f'strIngredient{i}'] for i in range(1, 15) if drink[f'strIngredient{i}']])
                instructions = drink['strInstructions']
                save_to_database(name, ingredients, instructions)
                self.result_list.addItem(name)
        conn.close()

    def show_recipe(self, item):
        name = item.text()
        conn = sqlite3.connect('cocktails.db')
        c = conn.cursor()
        c.execute("SELECT ingredients, instructions FROM cocktails WHERE name=?", (name,))
        result = c.fetchone()
        ingredients = result[0]
        instructions = result[1]
        self.recipe_window = RecipeWindow(name, ingredients, instructions)
        self.recipe_window.show()
        conn.close()


if __name__ == '__main__':
    conn = sqlite3.connect('cocktails.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS cocktails (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, ingredients TEXT, instructions TEXT)''')
    conn.commit()
    conn.close()
    app = QApplication(sys.argv)
    ex = CocktailDatabase()
    sys.exit(app.exec_())
