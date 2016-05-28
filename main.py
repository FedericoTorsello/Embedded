#!/usr/bin/env python3
from kivy.app import App

from kivy.uix.scatter import Scatter
from kivy.uix.label import Label
from kivy.uix.floatlayout import FloatLayout


class MyApp(App):
    def build(self):
        f = FloatLayout()
        s = Scatter()
        l = Label(text="Hello!", font_size=150)
        f.add_widget(s)
        f.add_widget(l)
        return f

if __name__ == '__main__':
    MyApp().run()
