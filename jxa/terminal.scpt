#!/usr/bin/env osascript -l JavaScript
// osacompile -l JavaScript -o finderterm.app terminal.scpt
// Info.plist: 'Application is agent (UIElement)' = 'YES'

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

// 用单引号包围，并把所有的 "'" 替换为 "'\''"
function shellescape(string) {
  return "'" + string.replace("'", "'\\''") + "'"
}

(function() {
  let app = Application.currentApplication();
  app.includeStandardAdditions = true;
  let se = Application('System Events');

  let finder = Application('Finder');
  let cwd = pathOfFinderWindow(finder);
  let terminal = Application('terminal');
  let length = terminal.windows.length;
  let cmd = 'cd ' + shellescape(cwd) + ' && open -a Terminal'
  terminal.doScript(cmd);
  //terminal.doScript(shellescape(cwd));
  //terminal.activate();
  return;
  for (let i = 0; i < 100; i++) {
    if (length != terminal.windows.length) {
      break
    }
    delay(0.01);
  }
  se.processes['Terminal'].windows[0].actions['AXRaise'].perform();
  se.keystroke('	', {using: 'command down'});
})();
