#!/usr/bin/env osascript -l JavaScript
// osacompile -l JavaScript -o finderterm.app terminal.scpt

/*
 * 获取最前面的 finder 窗口的所在目录
*/
function pathOfFinderWindow(finder) {
  	
  if (finder.windows.length) {
    // file:///home/eph/Desktop
    return decodeURI(finder.windows[0].target().url().slice(7));
  } else {
    return '';
  }
}

(function() {
  let app = Application.currentApplication();
  app.includeStandardAdditions = true;
  let se = Application('System Events');

  let finder = Application('Finder');
  let cwd = pathOfFinderWindow(finder);
  let terminal = Application('terminal');
  terminal.doScript(cwd);
  //terminal.activate();
  //se.keystroke('	', {using: 'command down'});
})();
