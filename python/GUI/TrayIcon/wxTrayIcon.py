#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function
import sys
import os
import os.path
import wx

TRAY_TOOLTIP = 'wxPython System Tray Demo'
TRAY_ICON = 'this.ico'

TRAY_ICON = os.path.abspath(os.path.join(os.path.dirname(__file__), TRAY_ICON))

def create_menu_item(menu, label, func):
    item = wx.MenuItem(menu, -1, label)
    menu.Bind(wx.EVT_MENU, func, id=item.GetId())
    menu.AppendItem(item)
    return item

class TaskBarIcon(wx.TaskBarIcon):
    def __init__(self, frame, iconpath=TRAY_ICON, tooltip=TRAY_TOOLTIP):
        self.frame = frame
        super(TaskBarIcon, self).__init__()
        self.set_icon(iconpath, tooltip)
        self.Bind(wx.EVT_TASKBAR_LEFT_DOWN, self.on_left_down)

    def CreatePopupMenu(self):
        menu = wx.Menu()
        #create_menu_item(menu, 'Say Hello', self.on_hello)
        #menu.AppendSeparator()
        create_menu_item(menu, 'Exit', self.on_exit)
        return menu

    def set_icon(self, path, tooltip):
        icon = wx.IconFromBitmap(wx.Bitmap(path))
        self.SetIcon(icon, tooltip)

    def on_left_down(self, event):
        #print('Tray icon was left-clicked.')
        pass

    def on_hello(self, event):
        print('Hello, world!')

    def on_exit(self, event):
        wx.CallAfter(self.Destroy)
        self.frame.Close()

class App(wx.App):
    def OnInit(self):
        frame = wx.Frame(None)
        self.SetTopWindow(frame)
        TaskBarIcon(frame)
        return True

def main(argv):
    app = App(False)
    app.MainLoop()

if __name__ == '__main__':
    sys.exit(main(sys.argv))
